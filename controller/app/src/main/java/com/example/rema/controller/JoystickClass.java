package com.example.rema.controller;

import android.content.Context;
import android.graphics.PorterDuff;
import android.os.CountDownTimer;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.graphics.Color;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.View;
import android.view.View.OnTouchListener;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

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
    public List <Float> positions = new ArrayList<Float>();
    int count=0;
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
    /**
     * // this draws the actual joystick on canvas which are two circles.
     * each drawcircle method draws one using 4 parameters including the raduis and the color  and the position in the canvas.
     * In this case is in the middle of the height and width of canvas
     */
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
            positions.add((float) 0);

            float displacement = (float) Math.sqrt(Math.pow(event.getX() - centerPosX, 2) + Math.pow(event.getY() - centerPosY, 2));

            positions.add(event.getY());
            if(event.getAction()!= event.ACTION_UP ) {

                if ( displacement < circRad) {
                    drawJoystick(event.getX(), event.getY());
                    joystickCallback.onJoystickMoved(event.getX(), event.getY());
                    if (positions.get(count) < positions.get(count+1) ) {

                        set_speed (event.getX(), event.getY() , true );
                    } else

                        set_speed (event.getX(), event.getY() , false );

                }

                else  {

                    float ratio = circRad / displacement;
                    float limitX = centerPosX + (event.getX() - centerPosX) * ratio;

                    float limitY = centerPosY + (event.getY() - centerPosY) * ratio;

                    drawJoystick(limitX, limitY);

                    joystickCallback.onJoystickMoved(event.getX(), (event.getY()));
/**
 try {
 //  TCPClient.sendCommands((int) get_angle(event.getX(), (event.getY())), 0);
 } catch (IOException e) {
 e.printStackTrace();
 }
 **/


                }

            } else if (event.getAction() == event.ACTION_UP) {

                drawJoystick(centerPosX, centerPosY);
            }


        }


        return true;
    }
    /**
     * This method allows any interaction with the joystick
     */
    public interface JoystickListener

    {

        void onJoystickMoved( float X, float Y);

    }

    private int  set_speed (float X , float Y , boolean direction ) {
        int accelerator=5;
        double angle= get_angle(X,Y);
        double coefficient=  10/Y;

        if ( Y > 0 && Y < centerPosY && direction   ) {
            accelerator+=accelerator*Math.sin(angle) +coefficient ;
        } else  if (!direction)  {

            accelerator+= Math.abs(accelerator*Math.cos(angle)) - 5*coefficient ;

        }

        return accelerator;
    }

    private double get_angle(float eventX, float eventY) {
        double y;
        float adjacent;
        double sinalpha;
        double opposite;
        float cosinalpha=0;
        float hypothenus;
        double alphaD=0;
        hypothenus = (float) Math.sqrt(Math.pow(eventX - centerPosX,2) + Math.pow(eventY - centerPosY,2));

        if (eventY <centerPosY ) {
            adjacent = centerPosY - eventY;
            cosinalpha= adjacent/hypothenus;

            if (eventX < centerPosX) {
                alphaD=Math.toDegrees(Math.acos(cosinalpha));
            } else

                alphaD=Math.toDegrees((2*Math.PI - Math.acos(cosinalpha)));


        } else if (eventY  >= centerPosY ) {
            opposite =  eventY ;
            sinalpha= opposite/hypothenus;

            if (eventX < centerPosX) {

                alphaD=Math.toDegrees(Math.PI/2 + Math.asin(sinalpha));

            } else

                alphaD=Math.toDegrees(Math.acos(cosinalpha));

        }

        return  alphaD;
    }

}
