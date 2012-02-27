package net.sniperbat.chaos;

import android.app.Activity;
import android.os.Bundle;

public class ChaosActivity extends Activity {
	GL2JNIView glView;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.glView = new GL2JNIView(getApplication());
        setContentView(R.layout.main);
    }

    @Override
    protected void onPause() {
        super.onPause();
        this.glView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        this.glView.onResume();
    }

    
}