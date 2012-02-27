package net.sniperbat.chaos;

public class ChaosLib {

     static {
         System.loadLibrary("chaos");
     }

    /**
     * @param width the current view width
     * @param height the current view height
     */
     //public static native void init(int width, int height);
     public static native void update();
}

