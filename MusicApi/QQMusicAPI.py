# coding: UTF-8
import requests
import timeit
# 屏蔽warning信息
requests.packages.urllib3.disable_warnings()


def get_playlist(playlist_id: str):
    """获取对应id的歌单信息和歌曲信息"""
    playlist_data = requests.get("https://v1.itooi.cn/tencent/songList?id={}".format(playlist_id))
    if playlist_data.status_code != 200:
        return []
    playlist_info = playlist_data.json()
    songs = requests.get("https://v1.itooi.cn/tencent/songList?id={}&format=1".format(playlist_id))
    if songs.status_code != 200:
        return []
    songs_info = songs.json()
    for song in songs_info["data"]:
        song["time"] = convert_interval_format(song["time"])

    return {
        "playlist_id": playlist_info["data"][0]["disstid"],
        "playlist_name": playlist_info["data"][0]["dissname"],
        "logo": playlist_info["data"][0]["logo"].replace("n=1", "n=3", 1),   # 把logo链接的参数n转换为非1/0的数(获得jpg直链)
        "songs": songs_info["data"]
    }


def get_search_result(keywords: str, page=1):
    """获得搜索结果"""
    # resp = requests.get("https://v1.itooi.cn/tencent/search?"
    #                         "keyword={}&type={}&pageSize=50&page={}&format=0".format(keywords, type, page))
    # if resp.status_code != 200:
    #     return []
    # songs = resp.json()
    # result = []
    # for song in songs["data"]["list"]:
    #     song_info = {"song_id": song["songmid"],
    #                  "song_name": song["songname"],
    #                  "singer": splice_singers(song["singer"]),
    #                  "album_id": song["albummid"],
    #                  "album_name": song["albumname"],
    #                  "durtion": convert_interval_format(song["interval"])
    #                  }
    #     result.append(song_info)
    # return result
    import json
    headers = {'User-Agent':
                   'Mozilla/5.0 (Windows NT 10.0; Win64; x64) '
                   'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36',
               'Referer': 'http://y.qq.com'}
    resp = requests.get("https://c.y.qq.com/soso/fcgi-bin/client_search_cp?cr=1&flag_qc=0&n=50&w={}&p={}".format(keywords, page),
                        headers=headers, verify=False).text[9:-1]
    songs = json.loads(resp)

    return [parse_search_result(song) for song in songs["data"]["song"]["list"]]
    # return json.dumps([parse_search_result(song) for song in songs["data"]["song"]["list"]])


def get_song_url(ids: list):
    """获取给定id的song_url"""
    result = []
    for song_id in ids:
        url = "https://v1.itooi.cn/tencent/url?id={}".format(song_id)
        result.append(url)
    return result


def get_song_lyric(song_id: str):
    """获取歌词"""
    # return api.song_lyric(song_id)
    resp = requests.get("https://v1.itooi.cn/tencent/lrc?id={}".format(song_id))
    if resp.status_code != 200:
        return ""
    return resp.text


def get_cover_url(song_id: str):
    """获取歌曲封面url(private)"""
    return "https://v1.itooi.cn/tencent/pic?id={}&isRedirect=0".format(song_id)


def splice_singers(info: list):
    """拼接歌手信息(private)"""
    singer = []
    for _singer in info:
        singer.append(_singer["name"])

    return "/".join(singer)


def convert_interval_format(interval: int):
    """转换interval的格式为 s:m(private)"""
    m = interval // 60
    s = interval % 60
    return "%02d" % m + ":" + "%02d" % s


def debug(result):
    print(result)
    print("返回的数据类型:", type(result))


def qqmusic():
    import json
    headers = {'User-Agent':
                   'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36',
               'Referer': 'http://y.qq.com'}
    resp = requests.get("https://c.y.qq.com/soso/fcgi-bin/client_search_cp?cr=1&flag_qc=0&n=50&w=薛之谦&p=1",
                        headers=headers, verify=False).text[9:-1]
    songs = json.loads(resp)

    return [parse_search_result(song) for song in songs["data"]["song"]["list"]]
    # with concurrent.futures.ProcessPoolExecutor() as executor:
    #     executor.map(deal_result, songs["data"]["song"]["list"])


def parse_search_result(song):
    return {"song_id": song["songmid"],
             "song_name": song["songname"],
             "singer": splice_singers(song["singer"]),
             "album_id": song["albummid"],
             "album_name": song["albumname"],
             "durtion": convert_interval_format(song["interval"]),
             "cover_url": "https://y.gtimg.cn/music/photo_new/T002R300x300M000{}.jpg?max_age=2592000".format(song["albummid"])
            }


if __name__ == '__main__':
    debug(get_playlist("2058988118"))    # 2646321242/1933161450

    # debug(qqmusic())
    # debug(get_search_result("薛之谦"))
    # print(timeit.timeit(stmt=qqmusic, number=1))
    # print(timeit.repeat(stmt=qqmusic, number=1, repeat=3))
    # debug(get_song_lyric("0039MnYb0qxYhV"))

    # debug(get_song_url(["0039MnYb0qxYhV", "001xd0HI0X9GNq", "001xd0HI0X9GNq", "001xd0HI0X9GNq"]))




