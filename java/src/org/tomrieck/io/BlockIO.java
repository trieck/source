package org.tomrieck.io;

import java.io.*;
import java.nio.channels.FileChannel;

public class BlockIO {

    private RandomAccessFile file;

    public BlockIO(String filename, String mode) throws FileNotFoundException {
        file = new RandomAccessFile(filename, mode);        
    }

    public void close() throws IOException {
        file.close();
        file = null;
    }

    public long getFileSize() throws IOException {
        return file.length();
    }

    public void readBlock(long blockno, Block block) throws IOException {
        seekBlock(blockno);
        block.read(getChannel());
    }

    public void writeBlock(long blockno, Block block) throws IOException {
        seekBlock(blockno);
        block.write(getChannel());
    }

    public void seekBlock(long blockno) throws IOException {
        file.seek(blockno * Block.BLOCK_SIZE);
    }

    private FileChannel getChannel() {
        return file.getChannel();
    }    

}
