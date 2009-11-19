package org.trieck.apps.odb;

public class RowData {

	private String id;

	public String getVal() {
		return val;
	}

	public void setVal(String val) {
		this.val = val;
	}

	private String val;

	private int type;
	private long createDate;
	private long lastAccessed;

	public RowData(String id, String val, int type, long createDate,
			long lastAccessed) {
		this.id = id;
		this.val = val;
		this.type = type;
		this.createDate = createDate;
		this.lastAccessed = lastAccessed;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public int getType() {
		return type;
	}

	public void setType(int type) {
		this.type = type;
	}

	public long getCreateDate() {
		return createDate;
	}

	public void setCreateDate(long createDate) {
		this.createDate = createDate;
	}

	public long getLastAccessed() {
		return lastAccessed;
	}

	public void setLastAccessed(long lastAccessed) {
		this.lastAccessed = lastAccessed;
	}

}
