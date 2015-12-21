package tv.danmaku.cap.media.player;

public interface CapLibLoader {
    public void loadLibrary(String libName) throws UnsatisfiedLinkError,
            SecurityException;
}
