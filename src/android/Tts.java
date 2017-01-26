package com.ibm.cio.plugins;

import android.util.Log;

import com.ibm.watson.developer_cloud.android.text_to_speech.v1.ITextToSpeechDelegate;
import com.ibm.watson.developer_cloud.android.text_to_speech.v1.TextToSpeech;
import com.ibm.watson.developer_cloud.android.text_to_speech.v1.dto.TTSConfiguration;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mihui on 5/29/16.
 */
public class Tts extends CordovaPlugin implements ITextToSpeechDelegate {

    public final String TAG = this.getClass().getSimpleName();

    private CallbackContext synthesizeContext = null;

    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
        this.initTTS();
    }

    public boolean execute(String action, JSONArray args, final CallbackContext callbackContext) throws JSONException {
        if(action.equals("synthesize")){
            String ttsText = args.getString(0);
            String customizationId = null;
            if(args.length() >= 2) {
                customizationId = args.getString(1);
            }
            this.synthesizeContext = callbackContext;
            this.synthesize(ttsText, customizationId);
            return true;
        }
        if(action.equals("listVoices")){
            this.listVoices(callbackContext);
            return true;
        }
        if(action.equals("setVoice")){
            String voiceText = args.getString(0);
            this.setVoice(callbackContext, voiceText);
            return true;
        }
        if(action.equals("stop")){
            this.stopTTS(callbackContext);
            return true;
        }
        return false;
    }

    private void stopTTS(CallbackContext callbackContext) {
        TextToSpeech.sharedInstance().stopAudio();
        callbackContext.success("Stopped audio Successfully");
    }

    private void setVoice(CallbackContext callbackContext, String voiceText) {
        TextToSpeech.sharedInstance().setVoice(voiceText);
        callbackContext.success(voiceText);
    }

    private void listVoices(final CallbackContext callbackContext) {
        this.cordova.getThreadPool().execute(new Runnable() {
            @Override
            public void run() {
                JSONArray result = new JSONArray();
                JSONObject list = TextToSpeech.sharedInstance().getVoices();

                try {
                    result.put(0, TextToSpeech.sharedInstance().getVoice());
                    result.put(1, list);
                    callbackContext.success(result);
                } catch (JSONException e) {
                    e.printStackTrace();
                    callbackContext.error(e.getMessage());
                }
            }
        });
    }

    private void synthesize(String text, String customizationId) {
        TextToSpeech.sharedInstance().synthesize(text, customizationId);
    }

    private void initTTS() {
        TTSConfiguration tConfig = new TTSConfiguration();
        // DISCLAIMER: please enter your credentials or token factory in the lines below

        tConfig.basicAuthUsername = "<your-username>";
        tConfig.basicAuthPassword = "<your-password>";
        tConfig.codec = TTSConfiguration.CODEC_OPUS;
        tConfig.appContext = this.cordova.getActivity().getApplicationContext();
        tConfig.voice = "en-US_AllisonVoice";

        TextToSpeech.sharedInstance().initWithConfig(tConfig, this);
    }

    @Override
    public void onTTSStart() {
        Log.d(TAG, "### onTTSStart ###");
    }

    @Override
    public void onTTSWillPlay() {
        Log.d(TAG, "### onTTSWillPlay ###");
        this.synthesizeContext.success("Synthesize Succeed");
    }

    @Override
    public void onTTSStopped() {
        Log.d(TAG, "### onTTSStopped ###");
    }

    @Override
    public void onTTSError(int statusCode) {
        Log.d(TAG, "### onTTSError: "+statusCode+" ###");
        this.synthesizeContext.error("Synthesize Failed");
    }
}
