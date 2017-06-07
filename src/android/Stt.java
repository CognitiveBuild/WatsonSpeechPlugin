package com.ibm.cio.plugins;

import android.util.Log;

import com.ibm.watson.developer_cloud.android.speech_to_text.v1.ISpeechToTextDelegate;
import com.ibm.watson.developer_cloud.android.speech_to_text.v1.SpeechToText;
import com.ibm.watson.developer_cloud.android.speech_to_text.v1.dto.STTConfiguration;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mihui on 5/29/16.
 */
public class Stt extends CordovaPlugin implements ISpeechToTextDelegate{

    private final String TAG = this.getClass().getSimpleName();

    private CallbackContext recognizeContext = null;

    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
        this.initSTT();
    }

    /**
     * execute plugin invokes
     *
     * @param action          The action to execute.
     * @param args            The exec() arguments.
     * @param callbackContext The callback context used when calling back into JavaScript.
     * @return boolean
     */
    public boolean execute(String action, JSONArray args, final CallbackContext callbackContext){
        if(action.equals("recognize")){
            this.recognizeContext = callbackContext;
            this.cordova.getThreadPool().execute(new Runnable() {
                @Override
                public void run() {
                    recognize();
                }
            });

            return true;
        }
        if(action.equals("endTransmission")){
            this.cordova.getThreadPool().execute(new Runnable() {
                @Override
                public void run() {
                    endTransmission();
                }
            });
            return true;
        }
        return false;
    }

    private void endTransmission() {
        SpeechToText.sharedInstance().endTransmission();
    }

    private void recognize() {
        SpeechToText.sharedInstance().recognize();
    }

    // initialize the connection to the Watson STT service
    private boolean initSTT() {
        STTConfiguration sConfig = new STTConfiguration(STTConfiguration.AUDIO_FORMAT_OGGOPUS, STTConfiguration.SAMPLE_RATE_OGGOPUS);
        // DISCLAIMER: please enter your credentials or token factory in the lines below
        sConfig.basicAuthUsername = "<your-username>";
        sConfig.basicAuthPassword = "<your-password>";

        SpeechToText.sharedInstance().initWithConfig(sConfig, this);

        return true;
    }

    private void sendStatus(final String status) {
        Log.d(TAG, "### Status: "+status);
    }

    @Override
    public void onOpen() {
        sendStatus("onOpen: successfully connected to the STT service");
    }

    @Override
    public void onBegin() { }

    @Override
    public void onError(int statusCode, String error) {
        sendStatus("onError: " + error);
        this.recognizeContext.error("Data error");
    }

    @Override
    public void onClose(int code, String reason, boolean remote) {
        try {
            sendStatus("onClose: connection closed: code: " + code + " reason: " + reason);
            JSONObject finalResult = new JSONObject();

            finalResult.put("iscompleted", "Yes");
            finalResult.put("isfinal", "Yes");
            finalResult.put("message", "");
            PluginResult result = new PluginResult(PluginResult.Status.OK, finalResult);
            result.setKeepCallback(true);
            this.recognizeContext.sendPluginResult(result);
            SpeechToText.sharedInstance().disConnect();
            SpeechToText.sharedInstance().stopRecording();
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void onMessage(String message) {
        try {
            JSONObject jObj = new JSONObject(message);

            JSONArray resultList = jObj.getJSONArray("results");

            for (int i = 0; i < resultList.length(); i++) {
                JSONObject obj = resultList.getJSONObject(i);
                JSONArray alternativeList = obj.getJSONArray("alternatives");
                if(alternativeList.length() > 0) {
                    String str = alternativeList.getJSONObject(0).getString("transcript");
                    boolean isFinal = obj.getString("final").equals("true");

                    JSONObject finalResult = new JSONObject();
                    finalResult.put("isfinal", isFinal ? "Yes" : "No");
                    finalResult.put("iscomplete", "No");
                    finalResult.put("message", str);
                    PluginResult result = new PluginResult(PluginResult.Status.OK, finalResult);
                    result.setKeepCallback(true);
                    this.recognizeContext.sendPluginResult(result);
                }
            }

        }
        catch (JSONException e) {
            e.printStackTrace();
            this.sendStatus("onMessage: Error parsing JSON");
            this.recognizeContext.error("Data error");
            SpeechToText.sharedInstance().stopRecognition();
        }
    }

    @Override
    public void onAmplitude(double v, double v1) {

    }

    @Override
    public void onData(byte[] bytes) {

    }
}
