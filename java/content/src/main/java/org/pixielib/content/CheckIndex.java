package org.pixielib.content;

import org.pixielib.util.StringUtil;
import org.pixielib.util.Timer;

import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.text.DecimalFormat;

public class CheckIndex {

    public CheckIndex() {
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("usage: CheckIndex db");
            System.exit(1);
        }

        Timer t = new Timer();

        CheckIndex chkindex = new CheckIndex();

        try {
            chkindex.checkIndex(args[0]);
        } catch (IOException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }

        System.out.printf("\n    elapsed time %s\n", t);
    }

    public void checkIndex(String db) throws IOException {

        Repository repos = Repository.getInstance();

        File index = repos.getIndexPath(db);
        try (RandomAccessFile file = new RandomAccessFile(index, "r")) {
            int magicno = file.readInt();
            if (magicno != Index.MAGIC_NO) {
                throw new IOException("file not in index format.");
            }

            System.out.printf("    Index filename: %s\n", index.getCanonicalPath());

            System.out.printf("    Index file size: %s bytes\n", StringUtil.comma(file.length()));

            int nfields = file.readInt();                    // number of fields
            System.out.printf("    Index field count: %s\n", StringUtil.comma(nfields));

            while (nfields-- > 0) {
                file.readUTF();                                            // index field
            }

            int nterms = file.readInt();
            System.out.printf("    Index term count: %s\n", StringUtil.comma(nterms));

            long hash_tbl_size = file.readLong();
            System.out.printf("    Hash table size: 0x%08x\n", hash_tbl_size);

            long hash_tbl_offset = file.readLong();
            System.out.printf("    Hash table offset: 0x%08x\n", hash_tbl_offset);

            // check the hash table
            file.seek(hash_tbl_offset);

            long nfilled = 0;
            for (long i = 0; i < hash_tbl_size; i++) {
                if (file.readLong() != 0) {
                    nfilled++;
                }
            }

            DecimalFormat df = new DecimalFormat("#0.00");

            System.out.printf("    Hash table fill factor: %s%%\n", df.format(100 * (nfilled / (double) hash_tbl_size)));
        }
    }
}
