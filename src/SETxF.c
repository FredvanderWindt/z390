/*----------------------------------------------------------------------------*\
 *
 *  Program Name : SETxF.c
 *  Author       : CGI (Antonio Vale Macedo)
 *  Created on   : 2019-08-17
 *  Description  : SETCF Interface between C and COBOL
 *                 Migration from HLASM to C - ING Rehosting project
 *
\*----------------------------------------------------------------------------*/

#include <jni.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include <SETxF.h>

#define SETCF_FUNCT_CODE_MAX_LENGTH    5
#define SETCF_PARAM_DATA_MAX_LENGTH    1024
#define SETCF_TOKEN_DATA_MAX_LENGTH    1024
#define SETCF_RETURN_MSG_MAX_LENGTH    1024

#define SETCF_ERR_NAME_TO_LONG        9999
#define SETCF_ERR_INVALID_FUNCTION    9998
#define SETCF_ERR_GET_TKN_LNG_FIELD   9997
#define SETCF_ERR_GET_TKN_DAT_FIELD   9996
#define SETCF_ERR_GET_RTR_COD_FIELD   9995
#define SETCF_ERR_GET_RTR_MSG_FIELD   9994
#define SETCF_ERR_SET_TKN_LNG_FIELD   9993
#define SETCF_ERR_SET_TKN_DAT_FIELD   9992
#define SETCF_ERR_SET_RTR_COD_FIELD   9991
#define SETCF_ERR_SET_RTR_MSG_FIELD   9990

INT APIENTRY SETCF(char*, int*, char*, int*, char*, int*, char*);

JNIEXPORT jint JNICALL Java_SETxF_SETCF
(JNIEnv *env, jobject obj, jstring a, jstring b, jstring c)
  {
	int ret = EXIT_FAILURE;

    jclass thisClass = (*env)->GetObjectClass(env, obj);
	jfieldID fidTknLng = NULL;
	jfieldID fidTknDat = NULL;
	jfieldID fidRtrCod = NULL;
	jfieldID fidRtrMsg = NULL;

	if ((fidTknLng = (*env)->GetFieldID(env, thisClass, "RQS_TKN_LNG", "Ljava/lang/String;")) == NULL)
		return ret = SETCF_ERR_GET_TKN_LNG_FIELD;
	else if ((fidTknDat = (*env)->GetFieldID(env, thisClass, "RQS_TKN_DAT", "Ljava/lang/String;")) == NULL)
		return ret = SETCF_ERR_GET_TKN_DAT_FIELD;
	else if ((fidRtrCod = (*env)->GetFieldID(env, thisClass, "RQS_RTR_COD", "Ljava/lang/String;")) == NULL)
		return ret = SETCF_ERR_GET_RTR_COD_FIELD;
	else if ((fidRtrMsg = (*env)->GetFieldID(env, thisClass, "RQS_RTR_MSG", "Ljava/lang/String;")) == NULL)
		return ret = SETCF_ERR_GET_RTR_MSG_FIELD;
	else
		ret = EXIT_SUCCESS;

	char cbl_fnc_cod[SETCF_FUNCT_CODE_MAX_LENGTH + 1];
	char cbl_prm_dat[SETCF_PARAM_DATA_MAX_LENGTH + 1];
	char cbl_tkn_dat[SETCF_TOKEN_DATA_MAX_LENGTH + 1];
	char cbl_rtr_msg[SETCF_RETURN_MSG_MAX_LENGTH + 1];
	int  cbl_prm_cnt = 0;
	int  cbl_tkn_lng = 0;
	int  cbl_rtr_cod = 0;
	int *pbl_prm_cnt = &cbl_prm_cnt;
	int *pbl_tkn_lng = &cbl_tkn_lng;
	int *pbl_rtr_cod = &cbl_rtr_cod;

	const char *fnc_cod = (*env)->GetStringUTFChars(env, a, NULL);
	const char *prm_cnt = (*env)->GetStringUTFChars(env, b, NULL);
	const char *prm_dat = (*env)->GetStringUTFChars(env, c, NULL);

	strcpy( cbl_fnc_cod, fnc_cod);
	strcpy( cbl_prm_dat, prm_dat);
	cbl_prm_cnt = atoi(prm_cnt);

	(*env)->ReleaseStringUTFChars(env, a, fnc_cod);
	(*env)->ReleaseStringUTFChars(env, b, prm_cnt);
	(*env)->ReleaseStringUTFChars(env, c, prm_dat);

	SETCF(
		cbl_fnc_cod,
		pbl_prm_cnt,
		cbl_prm_dat,
		pbl_tkn_lng,
		cbl_tkn_dat,
		pbl_rtr_cod,
		cbl_rtr_msg	);

	cbl_tkn_dat[cbl_tkn_lng] = 0;
	cbl_rtr_msg[SETCF_RETURN_MSG_MAX_LENGTH] = 0;
	char tmp_tkn_lng[24];
	char tmp_rtr_cod[24];
	sprintf(tmp_tkn_lng, "%d", cbl_tkn_lng);
	sprintf(tmp_rtr_cod, "%d", cbl_rtr_cod);

	jstring TknLng = NULL;
	jstring TknDat = NULL;
	jstring RtrCod = NULL;
	jstring RtrMsg = NULL;

	if ((TknLng = (*env)->NewStringUTF(env, tmp_tkn_lng)) == NULL)
		return ret = SETCF_ERR_SET_TKN_LNG_FIELD;
	if ((TknDat = (*env)->NewStringUTF(env, cbl_tkn_dat)) == NULL)
		return ret = SETCF_ERR_SET_TKN_DAT_FIELD;
	if ((RtrCod = (*env)->NewStringUTF(env, tmp_rtr_cod)) == NULL)
		return ret = SETCF_ERR_SET_RTR_COD_FIELD;
	if ((RtrMsg = (*env)->NewStringUTF(env, cbl_rtr_msg)) == NULL)
		return ret = SETCF_ERR_SET_RTR_MSG_FIELD;

	(*env)->SetObjectField(env, obj, fidTknLng, TknLng);
	(*env)->SetObjectField(env, obj, fidTknDat, TknDat);
	(*env)->SetObjectField(env, obj, fidRtrCod, RtrCod);
	(*env)->SetObjectField(env, obj, fidRtrMsg, RtrMsg);

	return EXIT_SUCCESS;
  }


