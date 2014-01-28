package s14_18551.lab1;

import java.io.FileNotFoundException;
import java.io.InputStream;

import android.net.Uri;
import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

public class AudioProcessActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_audio_process);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.audio_process, menu);
		return true;
	}
	
	private static final int SELECT_AUDIO = 100;

	public void select_audio(View view){
		Intent soundPickerIntent = new Intent();//, android.provider.MediaStore.Audio.Media.EXTERNAL_CONTENT_URI);
		soundPickerIntent.setType("*/*");
		soundPickerIntent.setAction(Intent.ACTION_GET_CONTENT);
		startActivityForResult(soundPickerIntent, SELECT_AUDIO);
	}
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent soundReturnedIntent) { 
	    super.onActivityResult(requestCode, resultCode, soundReturnedIntent); 

	    switch(requestCode) { 
	    case SELECT_AUDIO:
	        if(resultCode == RESULT_OK){  
	            Uri selectedImage = soundReturnedIntent.getData();
	            InputStream imageStream = null;
				try {
					imageStream = getContentResolver().openInputStream(selectedImage);
				} catch (FileNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				if(imageStream != null){
		            //Bitmap yourSelectedImage = BitmapFactory.decodeStream(imageStream);
		            TextView audio_loc = (TextView) findViewById(R.id.audio_file_name);
		    		Log.i("HERE", selectedImage.toString());
		            audio_loc.setText(selectedImage.toString());
				}
	        }
	    }
	}

}
