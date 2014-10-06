package org.pixielib.content;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class DocList {

    private List<Long> documents = new ArrayList<>();

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
        slice.documents.addAll(documents.subList(start, start + count));

        return slice;
    }

    public long getDoc(int index) {
        return documents.get(index);
    }

    public void add(long doc) {
        documents.add(doc);
    }

    public void addAll(Collection<Long> c) {
        documents.addAll(c);
    }

}
