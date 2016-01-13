

package tv.danmaku.cap.media.sample.eventbus;

import com.squareup.otto.Bus;

import java.io.File;

public class FileExplorerEvents {
    private static final Bus BUS = new Bus();

    public static Bus getBus() {
        return BUS;
    }

    private FileExplorerEvents() {
        // No instances.
    }

    public static class OnClickFile {
        public File mFile;

        public OnClickFile(String path) {
            this(new File(path));
        }

        public OnClickFile(File file) {
            mFile = file;
        }
    }
}
