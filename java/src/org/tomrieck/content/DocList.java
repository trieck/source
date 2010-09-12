package org.tomrieck.content;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class DocList {

    private List<Integer> documents = new ArrayList<Integer>();

    public DocList() {
    }

    public int size() {
        return documents.size();
    }

    public DocList slice(int start, int count) {
        start = Math.min(start, documents.size() - 1);
        start = Math.max(0, start);

        count = Math.min(count, documents.size() - start);
        count = Math.max(0, count);

        DocList slice = new DocList();
        slice.documents.addAll(documents.subList(start, start+count));

        return slice;
    }

    public int getDoc(int index) {
        return documents.get(index);
    }

    public void add(int doc) {
        documents.add(doc);
    }

    public void addAll(Collection<Integer> c) {
        documents.addAll(c);
    }
    
}
