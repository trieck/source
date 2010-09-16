package org.pixielib.apps.odb;

import org.pixielib.bencode.*;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class ODBClient {

    private static final int SERVER_PORT = 5001;
    private static final int WAIT_FOR_RESPONSE_TIME = 100;

    private String host = "";
    private Socket sock = null;

    public ODBClient(String host) {
        this.host = host;
    }

    /**
     * Request the creation of a new object pool
     *
     * @return the pool identifier
     * @throws IOException
     * @throws UnknownHostException
     */
    public String makePool() throws IOException, UnknownHostException {

        final BEDictionary request = new BEDictionary();
        request.set(Protocol.KEY_REQUEST_FNC, Protocol.FNC_MKPOOL);

        // send request to server
        final BEDictionary response = sendRequest(request);
        checkError(response);
        return response.getString(Protocol.KEY_RESPONSE_MSG);
    }

    /**
     * Create a new object in the pool
     *
     * @param poolid
     * @param type
     * @return the object id
     * @throws IOException
     * @throws UnknownHostException
     */
    String createObject(String poolid, int type) throws IOException,
            UnknownHostException {

        final BEDictionary request = new BEDictionary();
        request.set(Protocol.KEY_REQUEST_FNC, Protocol.FNC_CREATE);
        request.set(Protocol.KEY_POOL_ID, poolid);
        request.set(Protocol.KEY_REQUEST_OTYPE, type);

        final BEDictionary response = sendRequest(request);
        checkError(response);
        return response.getString(Protocol.KEY_RESPONSE_MSG);
    }

    /**
     * Create a new object in the pool with initial value
     *
     * @param poolid
     * @param object
     * @return the object id
     * @throws IOException
     * @throws UnknownHostException
     */
    String createObject(String poolid, BEObject object) throws IOException,
            UnknownHostException {

        final BEDictionary request = new BEDictionary();
        request.set(Protocol.KEY_REQUEST_FNC, Protocol.FNC_CREATE);
        request.set(Protocol.KEY_POOL_ID, poolid);
        request.set(Protocol.KEY_REQUEST_OTYPE, getObjectType(object));
        request.set(Protocol.KEY_OBJECT_VAL, object);

        final BEDictionary response = sendRequest(request);
        checkError(response);
        return response.getString(Protocol.KEY_RESPONSE_MSG);
    }

    /**
     * Create a new object in the pool with initial value, specifying key
     *
     * @param poolid
     * @param key
     * @param object
     * @return the object id
     * @throws IOException
     * @throws UnknownHostException
     */
    String createObject(String poolid, String key, BEObject object)
            throws IOException, UnknownHostException {

        final BEDictionary request = new BEDictionary();
        request.set(Protocol.KEY_REQUEST_FNC, Protocol.FNC_CREATE);
        request.set(Protocol.KEY_POOL_ID, poolid);
        request.set(Protocol.KEY_REQUEST_OTYPE, getObjectType(object));
        request.set(Protocol.KEY_OBJECT_ID, key);
        request.set(Protocol.KEY_OBJECT_VAL, object);

        final BEDictionary response = sendRequest(request);
        checkError(response);
        return response.getString(Protocol.KEY_RESPONSE_MSG);
    }

    String createString(String poolid, String val) throws IOException,
            UnknownHostException {
        return createObject(poolid, new BEString(val));
    }

    String createString(String poolid, String key, String val)
            throws IOException, UnknownHostException {
        return createObject(poolid, key, new BEString(val));
    }

    /**
     * Destroy an object in the pool
     *
     * @param poolid
     * @param objectid
     * @throws IOException
     * @throws UnknownHostException
     */
    void destroyObject(String poolid, String objectid) throws IOException,
            UnknownHostException {

        final BEDictionary request = new BEDictionary();
        request.set(Protocol.KEY_REQUEST_FNC, Protocol.FNC_DESTROY);
        request.set(Protocol.KEY_POOL_ID, poolid);
        request.set(Protocol.KEY_OBJECT_ID, objectid);

        final BEDictionary response = sendRequest(request);
        checkError(response);
    }

    BEObject getObject(String poolid, String objectid) throws IOException,
            UnknownHostException {

        final BEDictionary request = new BEDictionary();
        request.set(Protocol.KEY_REQUEST_FNC, Protocol.FNC_GET);
        request.set(Protocol.KEY_POOL_ID, poolid);
        request.set(Protocol.KEY_OBJECT_ID, objectid);

        final BEDictionary response = sendRequest(request);
        checkError(response);

        return response.get(Protocol.KEY_RESPONSE_MSG);
    }

    String getString(String poolid, String objectid) throws IOException,
            UnknownHostException {

        final BEObject object = getObject(poolid, objectid);
        if (object.getType() != BEObject.BET_STRING) {
            return "";
        }

        return ((BEString) object).toString();
    }

    void setObject(String poolid, String objectid, BEObject val)
            throws IOException, UnknownHostException {

        final BEDictionary request = new BEDictionary();
        request.set(Protocol.KEY_REQUEST_FNC, Protocol.FNC_SET);
        request.set(Protocol.KEY_POOL_ID, poolid);
        request.set(Protocol.KEY_OBJECT_ID, objectid);
        request.set(Protocol.KEY_OBJECT_VAL, val);

        final BEDictionary response = sendRequest(request);
        checkError(response);
    }

    void setString(String poolid, String objectid, String val)
            throws IOException, UnknownHostException {
        setObject(poolid, objectid, new BEString(val));
    }

    /**
     * Check the error status of the response object
     *
     * @param response
     * @throws IOException if an error was returned
     */
    private void checkError(BEDictionary response) throws IOException {
        final long ncode = response.getInt(Protocol.KEY_RESPONSE_CD);
        if (ncode != Protocol.E_OK) {
            throw new IOException(response.getString(Protocol.KEY_RESPONSE_MSG));
        }
    }

    /**
     * Send request to server
     *
     * @param request
     * @return the response
     * @throws IOException
     * @throws UnknownHostException
     */
    private BEDictionary sendRequest(BEDictionary request) throws IOException,
            UnknownHostException {

        // connect to the server
        connect();

        final OutputStream os = sock.getOutputStream();
        final InputStream is = sock.getInputStream();

        // send the object creation request
        BEEncoder.encode(request, os);
        os.flush();

        // wait and retrieve response from the server
        sleep(WAIT_FOR_RESPONSE_TIME);
        final BEObject response = BEDecoder.decode(is);

        if (response.getType() != BEObject.BET_DICT) {
            throw new IOException("bad response from server.");
        }

        return (BEDictionary) response;
    }

    /**
     * Connect to server
     *
     * @throws IOException
     * @throws UnknownHostException
     */
    private void connect() throws IOException, UnknownHostException {
        if (sock != null) {
            sock.close();
        }
        sock = new Socket(host, SERVER_PORT);
    }

    /**
     * Sleep number of milliseconds
     *
     * @param millis
     * @return
     */
    private boolean sleep(long millis) {
        try {
            Thread.sleep(millis);
        } catch (final InterruptedException e) {
            return false;
        }

        return true;
    }

    /**
     * Get protocol object type from object
     *
     * @param object
     * @return object type
     */
    private int getObjectType(BEObject object) {
        switch (object.getType()) {
            case BEObject.BET_INTEGER:
                return Protocol.OT_INTEGER;
            case BEObject.BET_STRING:
                return Protocol.OT_STRING;
            case BEObject.BET_LIST:
                return Protocol.OT_LIST;
            case BEObject.BET_DICT:
                return Protocol.OT_DICT;
        }

        return -1; // invalid
    }
}
