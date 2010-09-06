package org.tomrieck.io;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;

public class Block {

    public static final int BLOCK_SIZE = 4096;

    private ByteBuffer buffer;

    public Block() {
        buffer = ByteBuffer.allocate(BLOCK_SIZE);
    }

    public byte[] getBytes() {
        return buffer.array();
    }

    public void read(FileChannel channel) throws IOException {

        int nread;
        if ((nread = channel.read(buffer)) != BLOCK_SIZE) {
            throw new IOException("unable to read block");
        };        
    }

    public void write(FileChannel channel) throws IOException {

        int nwritten;
        if ((nwritten = channel.write(buffer)) != BLOCK_SIZE) {
            throw new IOException("unable to write block");
        }
        
    }
}
