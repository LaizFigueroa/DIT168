package com.example.fahddebbiche.joystick;

import android.content.Context;
import android.graphics.PorterDuff;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.graphics.Color;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.View;
import android.view.View.OnTouchListener;


class JoystickClass extends SurfaceView implements SurfaceHolder.Callback, OnTouchListener  {

    float  joyX;
    float  joyY;
    float  circRad;
    float  backcircRad;
    private int centerPosX;
    private int centerPosY;
    int A,R,G,B;
    private Paint PaintBase = new Paint();
    private Paint paintJoy = new Paint();
    private JoystickListener joystickCallback;
    int speedRegulator;
    private int colorLightGrey = Color.parseColor("darkgrey");

    void setupDimensions() {
        joyX = getWidth() / 2;

        joyY = getHeight() / 2;

        centerPosX = getWidth() / 2;

        centerPosY = getHeight() / 2;

        circRad = Math.min(getWidth(), getHeight()) / 2;

        backcircRad = Math.min(getWidth(), getHeight()) / 10;
    }

    private void init() {
        int color = (A & 0xff) << 24 | (R & 0xff) << 16 | (G & 0xff) << 8 | (B & 0xff);

        PaintBase.setColor(color);
        PaintBase.setAntiAlias(true);

        // int colo2r = ContextCompat.getColor(this.context, R.color.colorPrimaryDark);

        paintJoy.setColor(colorLightGrey);
        paintJoy.setAntiAlias(true);

    }


    public JoystickClass (Context c) {
        super(c);
        init();
        getHolder().addCallback(this);
        setOnTouchListener(this);

        if(c instanceof JoystickListener)

            joystickCallback = (JoystickListener) c;



    }

    public JoystickClass(Context context, AttributeSet attrs) {

        super(context, attrs);
        init();
        getHolder().addCallback(this);
        setOnTouchListener(this);

        if(context instanceof JoystickListener)

            joystickCallback = (JoystickListener) context;


    }

    public JoystickClass (Context c, AttributeSet a, int style) {
        super(c, a, style);
        init();
        getHolder().addCallback(this);
        setOnTouchListener(this);
        if(c instanceof JoystickListener)

            joystickCallback = (JoystickListener) c;


    }


    public void drawJoystick(float newX, float newY) {

        if(getHolder().getSurface().isValid()) {
            Canvas mycanvas = this.getHolder().lockCanvas();
            Paint colors = new Paint ();
            mycanvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR);
            colors.setARGB(255,50,50,50);
            mycanvas.drawCircle(joyX, joyY, circRad, colors);
            colors.setARGB(255,0,0,50);
            mycanvas.drawCircle(newX, newY, backcircRad, colors);

            getHolder().unlockCanvasAndPost(mycanvas);
        }

    }
    /**
     * This is called will be called when the size of the view is changing.
     * If you were just added to the view hierarchy, you're called with the old values of 0.
     */
    protected void onSizeChanged(int width, int height, int oldWidth, int oldheight) {
        super.onSizeChanged(width, height, oldWidth, oldheight);
        setupDimensions();
    }


    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {
        setupDimensions();
        drawJoystick(centerPosX,centerPosY);

    }

    @Override
    public void surfaceChanged(SurfaceHolder surfaceHolder, int i, int i1, int i2) {
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {
    }

    @Override
    public boolean onTouch( View v, MotionEvent event) {

        if(v.equals(this)) {

            float displacement = (float) Math.sqrt(Math.pow(event.getX() - centerPosX, 2) + Math.pow(event.getY() - centerPosY, 2));


            // double xy = Math.sqrt((Math.pow(event.getY(), 2) - Math.pow(event.getX(), 2)));
            // float bc = (float)(circRad*xy)/event.getY();
            // float newX =(float) Math.sqrt((Math.pow(circRad, 2) - Math.pow(bc, 2)));
            if(event.getAction()!= event.ACTION_UP ) {

                if ( displacement < circRad) {
                    drawJoystick(event.getX(), event.getY());
                    joystickCallback.onJoystickMoved(event.getX(), event.getY());
                }

                else  {
                    float ratio = circRad / displacement;
                    float limitX = centerPosX + (event.getX() - centerPosX) * ratio;

                    float limitY = centerPosY + (event.getY() - centerPosY) * ratio;

                    drawJoystick(limitX, limitY);

                    joystickCallback.onJoystickMoved(event.getX(), (event.getY()));
                    System.out.println( "outoutoutoutoutoutout xxxxxxxx  " + event.getX() + "outoutoutoutyyyyyy"  + event.getY());



                }



            } else if (event.getAction() == event.ACTION_UP) {

                drawJoystick(centerPosX, centerPosY);

            }
            joystickCallback.onJoystickMoved(event.getX(), event.getY());


        }


        return true;
    }

    public interface JoystickListener

    {

        void onJoystickMoved( float X, float Y);

    }

    private double exact_angle(float x) {
        double y;
        x = (float) Math.toRadians(x);


        return  y= Math.toDegrees(Math.tan(x));
    }


}




