package com.example.lab2a;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewFrame;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.Size;
import org.opencv.imgproc.Imgproc;

import android.os.Bundle;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import android.view.Menu;
import android.view.SurfaceView;
import android.view.View;
import android.view.WindowManager;

public class MainActivity extends Activity implements CvCameraViewListener2 {
	
	private CameraBridgeViewBase mOpenCvCameraView;
	private static String TAG = "InfoTag";
	
	static final int PICK_FILTER_REQUEST = 1;  // The request code

	
	// State Variables
	private boolean PERFORM_BLUR = false;
	private boolean PERFORM_EDGE_DETECTION = false;
	
	private void setPerformBlur(){
		PERFORM_BLUR = true;
		PERFORM_EDGE_DETECTION = false;
	}

	private void setEdgeDetection(){
		PERFORM_EDGE_DETECTION = true;
		PERFORM_BLUR = false;
	}
	
	private void setNoFilters(){
		PERFORM_EDGE_DETECTION = false;
		PERFORM_BLUR = false;
	}
	
	
	private BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
	    @Override
	    public void onManagerConnected(int status) {
	        switch (status) {
	            case LoaderCallbackInterface.SUCCESS:
	            {
	                Log.i(TAG, "OpenCV loaded successfully");
	                mOpenCvCameraView.enableView();
	                
	            } break;
	            default:
	            {
	                super.onManagerConnected(status);
	            } break;
	        }
	    }
	};

	@SuppressLint("NewApi")
	@Override
	protected void onCreate(Bundle savedInstanceState) {
	     Log.i(TAG, "called onCreate");
	     super.onCreate(savedInstanceState);
	     getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
	     setContentView(R.layout.activity_main);
	     mOpenCvCameraView = (CameraBridgeViewBase) findViewById(R.id.javaCameraView1);
	     mOpenCvCameraView.setVisibility(SurfaceView.VISIBLE);
	     mOpenCvCameraView.setCvCameraViewListener(this);
	     
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	@Override
	public void onResume()
	{
	    super.onResume();
	    OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_2_4_8, this, mLoaderCallback);
	}
	
	
	 @Override
	 public void onPause()
	 {
	     super.onPause();
	     if (mOpenCvCameraView != null)
	         mOpenCvCameraView.disableView();
	 }
	 
	 public void onDestroy() {
	     super.onDestroy();
	     if (mOpenCvCameraView != null)
	         mOpenCvCameraView.disableView();
	 }

	@Override
	public void onCameraViewStarted(int width, int height) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onCameraViewStopped() {
		// TODO Auto-generated method stub
		
	}

	
	public void launchListView(View view){
		
		Intent intent = new Intent(this, SelectFilter.class);
		startActivityForResult(intent, PICK_FILTER_REQUEST);
		
	}
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
	    // Check which request we're responding to
	    if (requestCode == PICK_FILTER_REQUEST) {
	        // Make sure the request was successful
	        if (resultCode == RESULT_OK) {
	            // The user picked a filter
	        	
	        	int filter_type =  data.getIntExtra("filter", 0);
	        	
	        	if(filter_type ==1 ){
	        		this.setPerformBlur();
	        	}
	        	
	        	else if(filter_type ==2 ){
	        		this.setEdgeDetection();
	        	}
	        	
	        	else{
	        		this.setNoFilters();
	        	}

	            
	        }
	    }
	}
	
	
	/**
	 * Function that performs applies the filters
	 */
	@Override
	public Mat onCameraFrame(CvCameraViewFrame inputFrame) {
	     Mat mRgba = inputFrame.rgba();
	     Mat tmp = mRgba.t();
	     Core.flip(mRgba.t(), tmp, 1);
	     Imgproc.resize(tmp, tmp, mRgba.size());

	     
	     Mat mOut = new Mat();
	     if(PERFORM_BLUR){
	    	 
	    	 Imgproc.blur(tmp, mOut, new Size(25,25));
	    	 
	     }
	     else if(PERFORM_EDGE_DETECTION){
	    	 Imgproc.Canny(tmp, mOut, 80, 90);
	     }
	     else{
	    	 mOut = tmp;
	     }
	     
	     
	     return mOut;
	}	

}
