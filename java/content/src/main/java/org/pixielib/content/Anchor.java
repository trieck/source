package org.pixielib.content;

/**
 * An anchor is a virtual term-location identifier in the document repository.
 * Each anchor is 8-bytes long. The bit-layout of an anchor is:
 * <p/>
 * ------------------ANCHOR------------------
 * 63......56 55....26 25.......16 15.......0
 * {FILE_NUM} {OFFSET} {FIELD_NUM} {WORD_NUM}
 * -------DOCID-------|
 * <p/>
 * FILE_NUM     : file # in repository (8-bits, 256 max number of files)
 * OFFSET       : offset into file where record is located (30-bits, max file size ~1GB)
 * FIELD_NUM    : field # in record (10-bits, 1,024 max top-level fields per record)
 * WORD_NUM     : word # of term in field (16-bits, 65,535 max words per field)
 * {DOC_ID}     : The upper 38-bits of the anchor represents the document id.
 */
public class Anchor implements Comparable<Anchor> {

    public static final byte FILENUM_BITS = 8;
    public static final byte OFFSET_BITS = 30;
    public static final byte FIELDNUM_BITS = 10;
    public static final byte WORDNUM_BITS = 16;

    private long anchorid;

    public Anchor(long anchorid) {
        this.anchorid = anchorid;
    }

    public static long makeAnchorID(int filenum, long offset, int fieldnum, int wordnum) {

        assert (filenum < (1 << FILENUM_BITS));
        assert (offset < (1 << OFFSET_BITS));
        assert (fieldnum < (1 << FIELDNUM_BITS));
        assert (wordnum < (1 << WORDNUM_BITS));

        long anchorid = ((long) (filenum & 0xFF) << (OFFSET_BITS + FIELDNUM_BITS + WORDNUM_BITS));
        anchorid |= (offset & 0x3FFFFFFF) << (FIELDNUM_BITS + WORDNUM_BITS);
        anchorid |= (fieldnum & 0x3FF) << WORDNUM_BITS;
        anchorid |= wordnum & 0xFFFF;

        return anchorid;
    }

    public long getAnchorID() {
        return anchorid;
    }

    public long getDocID() {
        return (anchorid >>> (FIELDNUM_BITS + WORDNUM_BITS));
    }

    @Override
    public int compareTo(Anchor d) {
        if (getDocID() < d.getDocID())
            return Integer.MIN_VALUE;

        if (getDocID() > d.getDocID())
            return Integer.MAX_VALUE;

        return (int) (anchorid - d.anchorid);
    }
}
