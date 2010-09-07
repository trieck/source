package org.tomrieck.content;

import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;
import java.nio.channels.Channels;

public class Search {

    public Search() {
    }

    public void search(String index_file, String term) throws IOException {

        RandomAccessFile f1 = new RandomAccessFile(index_file, "r");
        RandomAccessFile f2 = new RandomAccessFile(index_file, "r");

        int magicno = f1.readInt();
        if (magicno != Index.MAGIC_NO)
            throw new IOException("index bad file format.");

        f1.readLong();  // number of terms
        f1.readLong();  // concordance offset

        long hash_tbl_size = f1.readLong();     // size of hash table
        long hash_tbl_offset = f1.readLong();   // offset to the hash table

        long hash = Index.bucket_hash(term, hash_tbl_size);

        f1.seek(hash_tbl_offset + hash);

        long offset = f1.readLong();

        int nhits = 0;
        String sTerm;
        InputStream is = Channels.newInputStream(f2.getChannel());
        while (offset != 0) {   // linear-probing
            f2.seek(offset);
            sTerm = IOUtil.readString(is);
            if (sTerm.equals(term)) {
                nhits = f2.readInt();
                break;
            }
            offset = f1.readLong();
        }

        System.out.printf("    %d hits.\n", nhits);

        is.close();
        f2.close();
        f1.close();
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
