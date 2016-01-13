

package tv.danmaku.cap.media.sample.content;

import android.content.Context;
import android.database.Cursor;
import android.os.Environment;
import android.support.v4.content.AsyncTaskLoader;

import java.io.File;

public class PathCursorLoader extends AsyncTaskLoader<Cursor> {
    private File mPath;

    public PathCursorLoader(Context context) {
        this(context, Environment.getExternalStorageDirectory());
    }

    public PathCursorLoader(Context context, String path) {
        super(context);
        mPath = new File(path).getAbsoluteFile();
    }

    public PathCursorLoader(Context context, File path) {
        super(context);
        mPath = path;
    }

    @Override
    public Cursor loadInBackground() {
        File[] file_list = mPath.listFiles();
        return new PathCursor(mPath, file_list);
    }

    @Override
    protected void onStartLoading() {
        forceLoad();
    }
}
