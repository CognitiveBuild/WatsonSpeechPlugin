# Watson Speech SDK Plugin for iOS and Android
[![Language: Objective-C](https://img.shields.io/badge/objective--c-2.0-orange.svg?style=flat)](https://en.wikipedia.org/wiki/Objective-C)
[![Language: Java](https://img.shields.io/badge/java-android-orange.svg?style=flat)](http://java.com/)
[![Language: JavaScript](https://img.shields.io/badge/javascript-es5.0-orange.svg?style=flat)](https://www.javascript.com/)
[![GitHub license](https://img.shields.io/badge/license-Apache%202-blue.svg)](https://raw.githubusercontent.com/CognitiveBuild/WatsonSpeechPlugin/master/LICENSE)

# Installation

To install the Watson Speech Plugin in your Cordova Project, run in terminal:
```shell
cordova plugin add https://github.com/CognitiveBuild/WatsonSpeechPlugin.git
```

# Credentials

* iOS: Update your username/password of the Speech-to-Text and Text-to-Speech services in Credential.plist
* Android: Update in Java code of the native Plugins

# Basic JavaScript APIs

## Speech-to-Text
```javascript
WatsonSDK.SpeechToText.recognize(function(data){
    // data
    if(data.iscompleted === WatsonSDK.Constants.YES) {
        // connection closed, ready for another round of speech recognition
        return;
    }

    if(data.isfinal === WatsonSDK.Constants.YES) {
        // last transcript is returned, the WebSocket is automatically disconnected
    }
    // evaluate the transcription
    console.log(data.message);
}, function(error){
    // error
});
```
## Text-to-Speech

```javascript
var text = 'Hello World!';
WatsonSDK.TextToSpeech.synthesize(function(data){
    // success
}, function(error){
    // error
}, [text]);
```
## Text-to-Speech with Customizations

```javascript
var text = 'Hello World!';
var customization_id = 'your-customization-id';
WatsonSDK.TextToSpeech.synthesize(function(data){
    // success
}, function(error){
    // error
}, [text, customization_id]);
```

# Uninstall

To uninstall the Watson Speech Plugin from your Corodva Project, run in terminal:
```shell
cordova plugin remove WatsonSpeechPlugin
```

# License
Copyright 2017 GCG GBS CTO Office under [the Apache 2.0 license](LICENSE).
