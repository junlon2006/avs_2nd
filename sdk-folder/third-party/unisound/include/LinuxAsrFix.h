/**************************************************************************
 * Copyright (C) 2017-2017  Unisound
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 **************************************************************************
 *
 * Description : LinuxAsrFix.h
 * Author      : yzs.unisound.com
 * Date        : 2018.06.19
 *
 **************************************************************************/
#ifndef SDK_VUI_VUI_BASIC_SRC_RECOGN_LASR_LINUXASRFIX_H_
#define SDK_VUI_VUI_BASIC_SRC_RECOGN_LASR_LINUXASRFIX_H_

#define FOR_C_APP 1
#ifdef FOR_C_APP
#define YZS_CUBE_EXPORT __attribute__ ((visibility ("default")))
#else  // FOR_C_APP
#define YZS_CUBE_EXPORT
#endif  // FOR_C_APP
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef int (*PtrLpwCallback)(void *user_data);

#ifndef COMPILE_INTERNAL
/**
 * @function: create and initialize asr engine.
 * @paras:
 *         path_of_am: full directory where audio
 *                     models (am*.dat, tr*.dat) exists.
 *         path_of_grammar: file path(s) of grammar(s), for multiple grammars,
 *                          seperate each path with ';'
 *         port: decrepted. NO USE.
 * @return: status code
 */
int init(const char *path_of_am, const char *path_of_grammar, short port);

/**
 * @functions: set options of engine
 * @paras:
 *          id: option id
 *          value: option value
 * @return: status code
 * @note  : details will be provided in other docs.
 */
int setOptionInt(int id, int value);

/**
 * @functions: get options of engine
 * @paras:  id: option id
 * @return: value of id or -65535 for not support
 * @note  : details will be provided in other docs.
 */
int getOptionInt(int id);

/**
 * Deprecated
 */
int setOptionString(int id, const char *value);

/**
 * @function: set active grammar and turn the engine into start state
 * @para:
 *            grammar_tag: tag(s) for grammar(s), which will be activated.
 *                         For multiple grammars, seperated their domains with ';'
 *            am_index: index of audio model (for multiple audio models).
 *                      For single audio model distribution, please set this value to 0.
 * @return: status code
 */
int start(const char *grammar_tag, int am_index);

/**
 * @function: set the engine state to be stop. If the engine has not return
 *            any result before, this function will flush the audio and try to
 *            find result.
 * @return:   status code.
 */
int stop();

/**
 * @function: decoding
 * @para:
 *         raw_audio: audio data
 *         len: length of the input data in Bytes
 * @return: status code. if status code == ASR_RECOGNIZER_PARTIAL_RESULT,
 *          you can skip left audio and try to getResult.
 */
int recognize(char *raw_audio, int len);

/**
 * @function: retrieve recognition result from the engine
 * @return:   result or NULL for No-result
 */
char* getResult();

/**
 * Deprecated
 */
int cancel();

/**
 * @function: delete the engine.
 * @return:   status code
 */
void release();

/**
 * @function: get version number of the library
 * @return: string of version number
 */
const char* version();

/**
 * @function: set active decode net
 * @para:
 *         idx: index of decode net
 * @return: success: index of active decode net; failure:<0
 */
int setActiveNet(int idx);

/**
 * @function: output information of engine and model
 * @para:
 *         info_type: type of information(default 0)
 * @return: none
 */
void trackInfo(int info_type);

/**
 * @function: set callback function
 * @para:
 *         func_callback: callback function
 *         user_data: user data, passed back to callback function
 * @return: none
 */
void setCallback(PtrLpwCallback func_callback, void *user_data);

#else//COMPILE_INTERNAL

int lp_init(const char *path_of_am, const char *path_of_grammar, short port);
int lp_setOptionInt(int id, int value);
int lp_getOptionInt(int id);
int lp_setOptionString(int id, const char *value);
int lp_start(const char *grammar_tag, int am_index);
int lp_stop();
int lp_recognize(char *raw_audio, int len);
char *lp_getResult();
void lp_release();
const char* lp_version();
int lp_setActiveNet(int idx);
void lp_trackInfo(int info_type);
void lp_setCallback(PtrLpwCallback func_callback, void *user_data);

#endif
#ifdef __cplusplus
}
#endif
#endif
