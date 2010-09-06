package org.tomrieck.io;

import java.io.IOException;

public class BTree {

    /*
	 * Maximum depth of the b-tree
	 *
	 * Currently this is set to 5.
	 * The average number of probes p is about
	 * logM(N).  So, we can have about M^p
	 * items in the tree before we exceed the depth
	 * limits of the tree.
	 */
	private static final int MAXDEPTH = 5;

    private class Node {
        long next;          // link to next subpage
        long key;           // key for cell
        long val;           // value for cell, empty for internal nodes
    }

    private class PageHeader {
        byte flags;         // page flags
        long pagno;         // page number
        short cells;        // number of cells on the page
    }

    private class Page {
        PageHeader header;  // page header
        Node[] data;        // page data
    }

    private BlockIO io;         // underlying block i/o
    Page[] pages;              // pages in memory
    Page[] frames;             // spare frames for page split

    public BTree(String filename, String mode) throws IOException {
        io = new BlockIO(filename, mode);
        allocPages();

        if (io.getFileSize() != 0) {
            readPage(0, 0); // read page 0
        } else {
            // setLeaf(pages[0]);
            writePage(pages[0]);
        }

    }

    private void readPage(long pageno, int level) {
    }

    private void writePage(Page page) {

    }

    private void allocPages() {
        pages = new Page[MAXDEPTH];
        for (int i = 0; i < MAXDEPTH; i++) {
            pages[i] = makePage();
        }

        frames = new Page[2];
        frames[0] = makePage();
        frames[1] = makePage();
    }

    private Page makePage() {
        Page page = new Page();

        return page;
    }
    
    public void close() throws IOException {
        io.close();
    }

    public void insert(long key, long val) throws IOException {
        
    }

    public boolean lookup(long key, Long value) throws IOException {

        return false;
    }
    
}
