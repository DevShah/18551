package s14_18551.lab1;

import java.io.FileNotFoundException;
import java.io.InputStream;
import org.opencv.android.Utils;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.Size;
import org.opencv.imgproc.Imgproc;

import android.net.Uri;
import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.view.Menu;
import android.view.View;
import android.widget.ImageView;

public class ImageProcessActivity extends Activity {
	//private static final String TAG = "ImageProcess";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_image_process);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.image_process, menu);
		return true;
	}
	
	public void blur(View view){
		//grab image by id
		ImageView to_process = (ImageView) findViewById(R.id.image_we_will_process);
		//get the bitmap, convert to mat, blur
		Bitmap image_bitmap = ((BitmapDrawable) to_process.getDrawable()).getBitmap();
		int width = image_bitmap.getWidth();
		int height = image_bitmap.getHeight();
		Mat image_mat = new Mat(new Size(width,height), CvType.CV_32FC1);
		Utils.bitmapToMat(image_bitmap, image_mat);
		Imgproc.blur(image_mat, image_mat, new Size(25,25));
		//replace the image
		Utils.matToBitmap(image_mat, image_bitmap);
		to_process.setImageBitmap(image_bitmap);
		
		return;
	}
	
	public void canny(View view){
		//grab image by id
		ImageView to_process = (ImageView) findViewById(R.id.image_we_will_process);
		//get the bitmap, convert to mat, blur
		Bitmap image_bitmap = ((BitmapDrawable) to_process.getDrawable()).getBitmap();
		int width = image_bitmap.getWidth();
		int height = image_bitmap.getHeight();
		Mat image_mat = new Mat(new Size(width,height), CvType.CV_32FC1);
		Utils.bitmapToMat(image_bitmap, image_mat);
		Imgproc.Canny(image_mat, image_mat, 80, 90);
		//replace the image
		Utils.matToBitmap(image_mat, image_bitmap);
		to_process.setImageBitmap(image_bitmap);
	
		return;
	}
	
	public void reset(View view){
		ImageView to_process = (ImageView) findViewById(R.id.image_we_will_process);
		Bitmap refreshed = BitmapFactory.decodeResource(getResources(), R.drawable.group_pic_2);
		to_process.setImageBitmap(refreshed);
	}
	
	private static final int SELECT_PHOTO = 100;
	public void change_image(View view){
		Intent photoPickerIntent = new Intent(Intent.ACTION_PICK);
		photoPickerIntent.setType("image/*");
		startActivityForResult(photoPickerIntent, SELECT_PHOTO);
	}
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent imageReturnedIntent) { 
	    super.onActivityResult(requestCode, resultCode, imageReturnedIntent); 

	    switch(requestCode) { 
	    case SELECT_PHOTO:
	        if(resultCode == RESULT_OK){  
	            Uri selectedImage = imageReturnedIntent.getData();
	            InputStream imageStream = null;
				try {
					imageStream = getContentResolver().openInputStream(selectedImage);
				} catch (FileNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				if(imageStream != null){
		            Bitmap yourSelectedImage = BitmapFactory.decodeStream(imageStream);
		            ImageView to_process = (ImageView) findViewById(R.id.image_we_will_process);
		    		to_process.setImageBitmap(yourSelectedImage);
				}
	        }
	    }
	}
	
}
