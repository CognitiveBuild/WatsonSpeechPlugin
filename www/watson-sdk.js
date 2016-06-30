/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
*/

var exec = require('cordova/exec');

/**
 * Provides API.
 */
module.exports = {
    Constants: {
        YES: 'Yes',
        NO: 'No'
    },
    // Speech-To-Text, WatsonSDK.SpeechToText
    SpeechToText: {
        recognize : function(onSuccess, onFailure) {
            exec(onSuccess, onFailure, 'Stt', 'recognize', []);
        },
        endTransmission : function(onSuccess, onFailure) {
            exec(onSuccess, onFailure, 'Stt', 'endTransmission', []);
        },
        setModel : function(onSuccess, onFailure, modelName) {
            exec(onSuccess, onFailure, 'Stt', 'setModel', [modelName]);
        },
        listModels : function(onSuccess, onFailure) {
            exec(onSuccess, onFailure, 'Stt', 'listModels', []);
        }
    },
    // Text-To-Speech, WatsonSpeech.TextToSpeech
    TextToSpeech: {
        synthesize : function(onSuccess, onFailure, params) {
            exec(onSuccess, onFailure, 'Tts', 'synthesize', params);
        },
        stopAudio : function(onSuccess, onFailure) {
            exec(onSuccess, onFailure, 'Tts', 'stop', []);
        },
        setVoice : function(onSuccess, onFailure, voiceName) {
            exec(onSuccess, onFailure, 'Tts', 'setVoice', [voiceName]);
        },
        listVoices : function(onSuccess, onFailure) {
            exec(onSuccess, onFailure, 'Tts', 'listVoices', []);
        }
    }
};
