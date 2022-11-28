package org.pixielib.content;

public class Field {

    private final String name;     // field name
    private int word_count;  // current word count

    public Field(String name) {
        this.name = name;
        this.word_count = 0;
    }

    public String getName() {
        return name;
    }

    public int getWordCount() {
        return word_count;
    }

    public void setWordCount(int word_count) {
        this.word_count = word_count;
    }
}
