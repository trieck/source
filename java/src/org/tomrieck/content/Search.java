package org.tomrieck.content;

import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;
import java.nio.channels.Channels;

public class Search {

    public Search() {
    }

    public void search(String index_file, String term) throws IOException {

        String base = IOUtil.baseFilename(index_file);

        RandomAccessFile index = new RandomAccessFile(base + ".idx", "r");
        RandomAccessFile concord = new RandomAccessFile(base + ".dat", "r");

        int magicno = index.readInt();
        if (magicno != Index.MAGIC_NUMBER)
            throw new IOException("index bad file format.");

        magicno = concord.readInt();
        if (magicno != Concordance.MAGIC_NUMBER)
            throw new IOException("concordance bad file format.");

        long tableSize = index.readLong();

        long hash = Index.bucket_hash(term, tableSize);

        index.seek(12 + hash /* MAGIC_NO + TBL_SIZE */);

        long offset = index.readLong();
        if (offset == 0) {
            System.out.println("no hit.");
            return;
        }

        int nhits;
        String sTerm;
        InputStream is = Channels.newInputStream(concord.getChannel());
        while (offset != 0) {   // linear-probing
            concord.seek(offset);
            sTerm = IOUtil.readString(is);
            if (sTerm.equals(term)) {
                nhits = concord.readInt();
                System.out.printf("%d hits.\n", nhits);
                break;
            }

            offset = index.readLong();
        }

        is.close();
        concord.close();
        index.close();        
    }

    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("usage: Search index-file term");
            System.exit(1);
        }

        Search search = new Search();

        try {
            search.search(args[0], args[1]);

        } catch (IOException e) {
            System.err.println(e);
            System.exit(1);
        }
    }
}
