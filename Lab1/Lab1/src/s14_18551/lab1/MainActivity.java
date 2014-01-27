package s14_18551.lab1;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	public void imageProcess(View view){
		Intent intent = new Intent(this, ImageProcessActivity.class);
		startActivity(intent);
	}
	
	public void audioProcess(View view){
		Intent intent = new Intent(this, AudioProcessActivity.class);
		startActivity(intent);
	}

}
