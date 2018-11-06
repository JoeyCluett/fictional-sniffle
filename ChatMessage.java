package cpjlmsgs;

import cpjl.CPJL;
import cpjl.CPJL_Message;
import cpjl.Callback;
import cpjl.Topic;

public class ChatMessage extends CPJL_Message {

    public int flags;
    public String sender;
    public String msg;

    public Topic topic = new Topic();

    public ChatMessage(CPJL cpjl, String topic_name, Callback callback) throws Exception {
        super(cpjl, topic_name, callback);
        topic.add(Topic.INTEGER).add(Topic.STRING).add(Topic.STRING).done();
        topic.request(cpjl, topic_name);
    }

    public ChatMessage(CPJL cpjl, String topic_name) throws Exception {
        super(cpjl, topic_name);
        topic.add(Topic.INTEGER).add(Topic.STRING).add(Topic.STRING).done();
        topic.broadcast(cpjl, topic_name);
    }

    @Override
    public void putMessage() throws Exception {
        __cpjl.putString(__topic_name);

        __cpjl.putInt(flags);
        __cpjl.putString(sender);
        __cpjl.putString(msg);

    }

    @Override
    public void getMessage() throws Exception {
        flags = __cpjl.getInt();
        sender = __cpjl.getString();
        msg = __cpjl.getString();

    }

}
