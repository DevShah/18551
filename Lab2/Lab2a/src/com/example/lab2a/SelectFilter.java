package com.example.lab2a;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListAdapter;
import android.widget.ListView;

public class SelectFilter extends Activity {
	
	static final String[] Filters = new String[] { "No Filter", "Blur", "Canny"};

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_select_filter);
		
		ListView listView = (ListView)findViewById(R.id.list);
		
		ListAdapter adapter = new ArrayAdapter<String>(this, 
				android.R.layout.simple_list_item_1, Filters);
		listView.setAdapter(adapter);
		listView.setOnItemClickListener(new OnItemClickListener(){
			@Override
			public void onItemClick(AdapterView<?> parent, View view, int position, long id){
				Log.e("CLICK", "index: "+position);
				Intent resultIntent = new Intent();
				resultIntent.putExtra("filter", position);
				setResult(Activity.RESULT_OK, resultIntent);
				finish();
			}
		});
	}
	
	protected ListAdapter createAdapter()
    {

        // Create a simple array adapter (of type string) with the test values
        ListAdapter adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, Filters);

        return adapter;
    }

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.select_filter, menu);
		return true;
	}

}
