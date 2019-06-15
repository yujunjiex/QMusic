# encoding: UTF-8
from __future__ import print_function, unicode_literals, division, absolute_import
import os


class Constant(object):
    conf_dir = os.path.join(os.path.expanduser("~"), ".QMusic")    # .netease-musicbox
    download_dir = os.path.join(conf_dir, "cached")
    lyc_dir = os.path.join(conf_dir, "lyrics")
    lyc_netease = os.path.join(lyc_dir, "netease")
    lyc_qqmusic = os.path.join(lyc_dir, "qqmusic")
    config_path = os.path.join(conf_dir, "config.json")
    storage_path = os.path.join(conf_dir, "database.json")
    cookie_path = os.path.join(conf_dir, "cookie")
    log_path = os.path.join(conf_dir, "musicbox.log")
    cache_path = os.path.join(conf_dir, "nemcache")
