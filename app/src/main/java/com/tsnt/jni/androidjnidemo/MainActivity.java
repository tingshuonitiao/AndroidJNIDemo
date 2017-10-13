package com.tsnt.jni.androidjnidemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = (TextView) findViewById(R.id.sample_text);
        TextView tv1 = (TextView) findViewById(R.id.sample_text1);

        tv.setText(getStringFromJNIStatically());
        tv1.setText(getStringFromJNIDynamically());
    }

    //声明两个本地方法
    public native String getStringFromJNIStatically();

    public native String getStringFromJNIDynamically();

    //加载本地库native-lib
    static {
        System.loadLibrary("native-lib");
    }
}
