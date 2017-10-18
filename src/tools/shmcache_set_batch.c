#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logger.h"
#include "shared_func.h"
#include "shmcache.h"

#define NOUSE(v) (void)(v);

static void usage(const char *prog)
{
    fprintf(stderr, "shmcache set key value.\n"
         "Usage: %s [config_filename] <key> <value> <ttl>\n", prog);
}

int main(int argc, char *argv[])
{
        int result;
    int index;
    char *config_filename;
    struct shmcache_context context;
    struct shmcache_key_info key;
    char *value = "{ \"_id\" : ObjectId(\"59e6f9c528a544ec4fc75ca2\"), \"resource_id\" : NumberLong(\"1508309445527778\"), \"country\" : \"IN\", \"lang\" : \"en\", \"category\" : 1, \"sub_class\" : -1, \"create_time\" : NumberLong(\"1508309343969\"), \"pub_time\" : NumberLong(\"1508309335167\"), \"title\" : \"Yes, I was groped and yet I kept quiet\", \"url\" : \"http://timesofindia.indiatimes.com/life-style/relationships/soul-curry/yes-i-was-groped-and-yet-i-kept-quiet/articleshow/59967624.cms\", \"images\" : [ { \"origin\" : { \"url\" : \"https://static.toiimg.com/thumb/msid-59967711/59967711.jpg?resizemode=4&width=400&pl=124868\", \"width\" : 400, \"height\" : 293, \"size\" : 31113 }, \"list_small\" : { \"width\" : 224, \"height\" : 162, \"size\" : 3172, \"url\" : \"http://img.news.apusapps.com/news/img/20171018/2d3fe686feea274f6ed750e717b1fe4e.webp\" } } ], \"source\" : \"The Times Of India\", \"share_link\" : { \"2\" : \"82jju5\", \"4\" : \"788otc\", \"1\" : \"94v3u6\" }, \"summary\" : \"\", \"article\" : { \"html\" : \"<div class=\\\"news-mainbody\\\"><img align=\\\"left\\\" msid=\\\"59967711\\\" news-image-src=\\\"https://static.toiimg.com/thumb/msid-59967711/59967711.jpg?resizemode=4&width=400&pl=124868\\\" src=\\\"data:image/gif;base64,R0lGODlhAQABAIAAAP///wAAACH5BAEAAAAALAAAAAABAAEAAAICRAEAOw==\\\" data-size=\\\"[400,293]\\\" data-src=\\\"https://static.toiimg.com/thumb/msid-59967711/59967711.jpg?resizemode=4&width=400&pl=124868\\\"><div class=\\\"article-txt clearfix article-section\\\"><div class=\\\"clearfix\\\">\\n\\n  It is not easy to write about this. Almost fifteen years have gone by, but I still remember it vividly. The sepia-tinted image of a crowded public bus, a confused girl and a man standing behind her, his face still unknown till date.\\n  <br>\\n  <br>\\n  First time of anything is special—your first day in college, the first time you sit behind a steering wheel, your first step. But I still look back in anger when I recall the first time I travelled in a public bus.\\n  <br>\\n  <br>\\n  I was used to being chaperoned so the idea of travelling alone, even if it's for a few kilometers, made me really look forward to it. After my mother called up the absentee driver for the hundredth time, she finally gave up. \\\"Are you sure you know which bus you need to take. Why don't you take an autorickshaw instead,\\\" she asked in a worried voice. \\\"It's just a few kilometers, Ma,\\\" saying this, I quickly planted a kiss on her cheeks before leaving, a habit that I haven't yet outgrown.\\n  <br>\\n  <br><div class=\\\"ad1 MREC ov_ad_pc\\\"><div class=\\\"content_placeholder\\\"></div></div>\\n  It was a humid July morning. I let three buses pass before I mounted the one I believed to be less crowded. The dense air inside the bus carried the acrid smell of stale perfumes, it even had traces of the familiar rusty smell of metal window sills of old buses. The first few minutes were a struggle but I didn't give up.\\n  <br>\\n  <br>\\n  As I slowly adjusted to the noise, smell and the people around, I felt something strange. It was worse than suffocation. I didn't even turn back to find what or who it was, not because the bus was too crowded—I couldn't admit that I was scared. The slow push became persistent. I could almost feel a weird hardness pressing me from behind.\\n  <br>\\n  <br>\\n  I knew what it was, I knew there was a man standing behind me, I knew I should turned back and given him a piece of my mind but I just stood there doing nothing. I was a 17-year-girl, too old to not know what this meant but too young and inexperienced to yet find a voice. I got down from the bus after twenty-long minutes of suffocating silence.\\n  <br>\\n  <div class=\\\"ad1 NativeInarticle padB10 padT10\\\"><div class=\\\"content_placeholder id_pcholder\\\"><ul class=\\\"clearfix\\\"><li><div class=\\\"content_slot\\\"></div></li></ul></div></div>\\n  I had heard my friends discussing how they have experienced groping and how they could never gather the courage to inform this. That day, I sat down with my friends and told them what I had gone through in the morning. A girl even advised me to carry a safety pin while travelling so that I can poke a person when he comes too close. I even made up my mind to tell my mother. But when I reached home, the same silence gripped me. What do I tell her? How do I explain that I just stood still while a man rubbed his erection on my back in a crowded bus. I didn't even had the courage to utter the word erection then!\\n  <br>\\n  <br>\\n  Almost all girls experience groping or any kind of sexual contact while growing up. It might happen in your school, like one of my friends revealed how she was groped by a boy from another school during a science exhibition. One of my colleagues, a man, was repeatedly groped by their male servant at home. He couldn't overcome this even after thirty years.\\n  <br>\\n  <br>\\n  How do we stop this? How can we break our silence when the situation demanded? Some, like the girl from my college, will learn to be armed with a safety pin, if required. But what about the others who still shudder at the thought of closed doors and a familiar face?\\n  <br>\\n  <br>\\n  <strong>- By Rupamudra Kataki</strong>\\n  \\n\\n</div></div></div>\", \"tags\" : [ \"First time\", \"bus\", \"man\" ], \"third_party_links\" : [ ] }, \"status\" : 0, \"news_type\" : 0, \"latest_interest\" : 0, \"extra\" : { \"image_source\" : [ \"From article\" ] }, \"account\" : { \"need_rewrite\" : false, \"name\" : \"The Times Of India\", \"id\" : 1509968566 }, \"behavior\" : { \"read\" : 14, \"share\" : 1 } }";
    int value_len = strlen(value);
    int ttl = 86400;

    if (argc >= 2 && (strcmp(argv[1], "-h") == 0 ||
                strcmp(argv[1], "help") == 0 ||
                strcmp(argv[1], "--help") == 0))
    {
        usage(argv[0]);
        return 0;
    }
    //if (argc < 4) {
    //    usage(argv[0]);
    //    return EINVAL;
    //}

    config_filename = "/etc/libshmcache.conf";
    if (isFile(argv[1])) {
        //if (argc < 5) {
        //    usage(argv[0]);
        //    return EINVAL;
        //}
        config_filename = argv[1];
        index = 2;
    } else {
        index = 1;
    }

        log_init();
    if ((result=shmcache_init_from_file(&context, config_filename)) != 0) {
        return result;
    }

    NOUSE(index);

    int count = 100;
    if(argc > 2) {
        count = atoi(argv[index++]);
    }

    char pkey[20] = {"key111"};
    size_t i=0;
    for(i=0; i<count; i++) {
        snprintf(pkey, sizeof(pkey), "key-%09lu", i);
        key.data = pkey;
        key.length = strlen(key.data);
        //value = argv[index++];
        //value_len = strlen(value);
        result = shmcache_set(&context, &key, value, value_len, ttl);
        if (result == 0) {
            printf("set key: %s success.\n", key.data);
        } else {
            fprintf(stderr, "set key: %s fail, errno: %d\n", key.data, result);
        }
    }

        return result;
}
