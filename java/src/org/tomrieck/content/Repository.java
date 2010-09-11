package org.tomrieck.content;

import org.tomrieck.util.Config;

import java.io.File;
import java.io.IOException;

public class Repository {

    private Config config;

    private static Repository instance;

    private Repository() throws IOException {
        config = Config.getInstance();
    }

    public static synchronized Repository getInstance() throws IOException {

       if (instance != null)
           return instance;

       instance = new Repository();

       return instance;
    }

    public File getPath() throws IOException {
        String repos = config.getProperty("content.repos");
        if (repos.length() == 0)
            throw new IOException(String.format("content.repos not set."));

        File dir = new File(repos);
        checkRepos(dir);

        return dir;
    }

    public File mapPath(String db) throws IOException {
        File repos = getPath();

        String path = repos.getCanonicalPath() + "/" + db;

        File f = new File(path).getCanonicalFile();

        checkRepos(f);

        return f;
    }

    public File getIndexPath(String db) throws IOException {
        File outpath = mapPath(db);

        return new File(outpath.getCanonicalPath() + "/" + db + ".idx").getCanonicalFile();
    }

    private void checkRepos(File dir) throws IOException {
        if (!dir.isDirectory()) {
            throw new IOException(
                String.format("\"%s\" is not a repository.", dir.getCanonicalPath())
            );
        }
    }

    /* get file for document number */
    public File getFile(String db, int docnum) throws IOException {
        File dir = mapPath(db);

        String dirpath = dir.getCanonicalPath();

        String filename = String.format("%s/%04x.xml", dirpath, docnum);

        return new File(filename).getCanonicalFile();
    }
}
