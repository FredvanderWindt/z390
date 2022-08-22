/*----------------------------------------------------------------------------*\
 *
 *  Program Name : SETxF.java
 *  Author       : CGI (Antonio Vale Macedo)
 *  Created on   : 2019-08-17
 *  Description  : SETCF Interface between java and C
 *                 Migration from HLASM to C - ING Rehosting project
 *
\*----------------------------------------------------------------------------*/

public class SETxF {

	private static String SETCF_ERR_NAME_TO_LONG      = "9999";
	private static String SETCF_ERR_INVALID_FUNCTION  = "9998";
	private static String SETCF_ERR_GET_TKN_LNG_FIELD = "9997";
	private static String SETCF_ERR_GET_TKN_DAT_FIELD = "9996";
	private static String SETCF_ERR_GET_RTR_COD_FIELD = "9995";
	private static String SETCF_ERR_GET_RTR_MSG_FIELD = "9994";
	private static String SETCF_ERR_SET_TKN_LNG_FIELD = "9993";
	private static String SETCF_ERR_SET_TKN_DAT_FIELD = "9992";
	private static String SETCF_ERR_SET_RTR_COD_FIELD = "9991";
	private static String SETCF_ERR_SET_RTR_MSG_FIELD = "9990";
	private static String SETCF_ERR_LOAD_FQMSETCF_LIB = "9989";
	private static String SETCF_ERR_LOAD_SETCF_LIB    = "9988";
		
	private String RQS_TKN_LNG = ""; 
	private String RQS_TKN_DAT = "";
	private String RQS_RTR_COD = "";
	private String RQS_RTR_MSG = "";

	public native int SETCF( String RQS_FNC_COD,String RQS_PRM_CNT, String RQS_PRM_DAT);							  

	public SETxF(){ 
		loadLibs(); 
	}

    public void loadLibs() {
		String loadLibPath = null;			
		try {
			loadLibPath = System.getenv("ESI_LOADDIR") + "\\" + "FQMSETCF.dll";	
			System.load(loadLibPath);
		}
		catch (UnsatisfiedLinkError ule) {
			System.err.println("Application Error Loading FQMSETCF dll: " + ule.getMessage ());
			setRQS_RTR_MSG("Application Error Loading FQMSETCF dll: " + ule.getMessage ());
			setRQS_RTR_COD(SETCF_ERR_LOAD_FQMSETCF_LIB);
		}		
		try {
			loadLibPath = System.getenv("ESI_LOADDIR") + "\\" + "SETxF.dll";	
			System.load(loadLibPath);
		}
		catch (UnsatisfiedLinkError ule) {
			System.err.println("Application Error Loading FQMSETCF dll: " + ule.getMessage ());			
			setRQS_RTR_MSG("Application Error Loading SETxF dll: " + ule.getMessage ());
			setRQS_RTR_COD(SETCF_ERR_LOAD_SETCF_LIB);
		}							
	}

	public String getRQS_TKN_LNG() {
		return RQS_TKN_LNG;
	}

	public void setRQS_TKN_LNG(String rQS_TKN_LNG) {
		RQS_TKN_LNG = rQS_TKN_LNG;
	}

	public String getRQS_TKN_DAT() {
		return RQS_TKN_DAT;
	}

	public void setRQS_TKN_DAT(String rQS_TKN_DAT) {
		RQS_TKN_DAT = rQS_TKN_DAT;
	}

	public String getRQS_RTR_COD() {
		return RQS_RTR_COD;
	}

	public void setRQS_RTR_COD(String rQS_RTR_COD) {
		RQS_RTR_COD = rQS_RTR_COD;
	}

	public String getRQS_RTR_MSG() {
		return RQS_RTR_MSG;
	}

	public void setRQS_RTR_MSG(String rQS_RTR_MSG) {
		RQS_RTR_MSG = rQS_RTR_MSG;
	}

}