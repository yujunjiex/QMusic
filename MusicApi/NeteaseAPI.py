# coding: UTF-8
from utils import create_dir, create_file
from const import Constant

# 初始化缓存
create_dir(Constant.conf_dir)
create_dir(Constant.download_dir)
create_dir(Constant.lyc_dir)
create_dir(Constant.lyc_netease)
create_dir(Constant.lyc_qqmusic)
create_dir(Constant.download_dir)
create_file(Constant.storage_path)
create_file(Constant.log_path, default="")
create_file(Constant.cookie_path, default="#LWP-Cookies-2.0\n")

from api import NetEase, Parse
from storage import Storage
from hashlib import md5

api = NetEase()
storage = Storage()
storage.load()  # 载入存储的信息

user = storage.database["user"]
account = user["username"]
md5pass = user["password"]
userid = user["user_id"]
username = user["nickname"]


def request_api(func, *args):
    """需要登录功能的请求方式(private)"""
    result = func(*args)
    if result:
        return result
    if not login():
        return False
    return func(*args)


def login(username="", passwd=""):
    """登录"""
    global account, md5pass
    if account and md5pass:
        login_account, login_md5pass = account, md5pass
    else:
        login_account, login_md5pass = username, md5(passwd.encode('utf8')).hexdigest()

    resp = api.login(login_account, login_md5pass)
    if resp["code"] == 200:
        user_id = resp["account"]["id"]
        nickname = resp["profile"]["nickname"]
        storage.login(login_account, login_md5pass, user_id, nickname)
        storage.save()
        return True
    else:
        storage.logout()
        storage.save()
        return False


def logout():
    """注销登录"""
    storage.logout()
    storage.save()
    return True


def get_song_url(ids: list):
    """获取给定id的song_url"""
    return api.songs_url(ids)[0]["url"]


def get_top_list():
    """获取排行榜信息
        :return 排行榜list
    """
    return api.toplists


def get_top_songlist(idx: int):
    """获取排行榜歌单中的歌曲"""
    songs = api.top_songlist(idx)
    return api.dig_info(songs, "songs")


def get_artists(offset=0, limit=100):
    """获取歌手榜单
        :argument
            offset: 偏移值
            limit: 一次获取的最大值

        :return 含歌手信息的list
    """
    artists = api.top_artists(offset, limit)
    return api.dig_info(artists, "artists")


def get_artists_songs(artist_id: int):
    """获取歌手的热门50首单曲"""
    songs = api.artists(artist_id)
    return api.dig_info(songs, "songs")


def get_new_album(offset=0, limit=50):
    """新碟上架"""
    albums = api.new_albums(offset, limit)
    return api.dig_info(albums, "albums")


def get_songs_from_album_id(album_id: int):
    """获取album中的歌曲信息"""
    songs = api.album(album_id)
    return api.dig_info(songs, "songs")


def get_album_info(album_id: int):
    """获取对应唱片id的唱片信息"""
    album = api.album_info(album_id)
    return album


def get_user_playlist():
    """获取用户歌单"""
    global userid
    myplaylist = request_api(api.user_playlist, userid)
    return api.dig_info(myplaylist, "top_playlists")


def get_recommend_playlist():
    """每日推荐的歌曲"""
    myplaylist = request_api(api.recommend_playlist)
    if myplaylist == -1:
        return
    return api.dig_info(myplaylist, "songs")


def get_recommend_resource():
    """每日推荐的歌单
    :return
        未登录则返回空list
    """
    play_resource = request_api(api.recommend_resource)
    return api.dig_info(play_resource, "top_playlists")


def get_fmsongs():
    """私人FM"""
    # data = request_api(api.personal_fm)   # 处理登录
    data = None
    if not data:
        return []
    return api.dig_info(data, "fmsongs")


def get_top_playlists(category="全部", order="hot", offset=0, limit=50):
    """歌单（流行）"""
    playlists = api.top_playlists(category=category, order=order, offset=offset, limit=limit)
    return api.dig_info(playlists, "top_playlists")


def get_songs_from_playlist_id(playlist_id: int):
    """获取歌单id对应歌单中的所有歌曲信息"""
    songs = api.playlist_detail(playlist_id)
    return api.dig_info(songs, "songs")


def get_search_result(keywords: str, stype=1, offset=0):
    """获取搜索结果(默认单曲搜索)
        :argument
        stype: 搜索单曲(1)，歌手(100)，专辑(10)，歌单(1000)，用户(1002) *(type)*
        ...

        :return 搜索结果的dict
    """
    data = api.search(keywords, stype, offset)
    # print("总数：", data['songCount'])
    # print(data)
    return api.dig_info(data.get("songs", []), "songs")


def get_song_lyric(song_id: str):
    """获取歌词"""
    return api.song_lyric(song_id)


def debug(result):
    print(result)
    print("返回的数据类型:", type(result))


if __name__ == '__main__':
    "获取排行榜歌单，歌单内歌曲信息"
    # debug(get_top_list())
    # debug(get_top_songlist(0))
    # debug(get_song_url([1367368790]))

    "获取歌手信息"
    # debug(get_artists())
    # debug(get_artists_songs(5781))    # 热门五十首的api获取不到单曲封面，应该在播放时获取

    "新碟上架(暂时不用)"
    # debug(get_new_album())
    # debug(get_songs_from_album_id(78767132))      # 专辑的歌曲封面一致(用get_album_info获取)
    # debug(api.album(78767132))
    # # debug(api.album_img(78767132))
    # debug(get_album_info(78767132))   # 拿歌单信息(包括封面)

    "流行歌单"
    # debug(get_top_playlists())  # (已添加封面信息)
    # debug(get_songs_from_playlist_id(766660144))   # 少了一个时长信息 (改写parse获取dt 已解决)

    "搜索"
    debug(get_search_result("周杰伦"))    # TODO:获取封面图片
    # get_search_result("周杰伦", offset=50)    # offset存在问题

    # debug(get_song_url([536570450]))

    "用户登陆，用户歌单及每日推荐"
    # login("15070329437", "yu414826")
    # logout()
    # debug(get_user_playlist())
    # debug(get_songs_from_playlist_id(490995549))
    # debug(get_recommend_playlist())     # 每日歌曲推荐
    # debug(get_recommend_resource())   # 每日歌单推荐

    "歌词"
    # debug(get_song_lyric("424264505"))    # 返回的str直接写到临时的lyric文件中,以歌曲名命名
    # debug(api.songs_detail([4878132, 4878133]))

    # print(api.songs_url([424264505])[0]["url"])
    # print(api.playlist_catelogs())



