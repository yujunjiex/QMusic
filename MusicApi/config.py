# encoding: UTF-8
from __future__ import print_function, unicode_literals, division, absolute_import
import json
import os
from future.builtins import open

from singleton import Singleton
from const import Constant
from utils import utf8_data_to_file


class Config(Singleton):
    def __init__(self):
        if hasattr(self, "_init"):
            return
        self._init = True

        self.path = Constant.config_path
        self.default_config = {
            "version": 8,
            "cache": {
                "value": False,
                "default": False,
                "describe": (
                    "A toggle to enable cache function or not. "
                    "Set value to true to enable it."
                ),
            },
            "music_quality": {
                "value": 0,
                "default": 0,
                "describe": (
                    "Select the quality of the music. "
                    "May be useful when network is terrible. "
                    "0 for high quality, 1 for medium and 2 for low."
                ),
            },
        }
        self.config = {}
        if not os.path.isfile(self.path):
            self.generate_config_file()

        with open(self.path, "r") as f:
            try:
                self.config = json.load(f)
            except ValueError:
                self.generate_config_file()

    def generate_config_file(self):
        with open(self.path, "w") as f:
            utf8_data_to_file(f, json.dumps(self.default_config, indent=2))

    def save_config_file(self):
        with open(self.path, "w") as f:
            utf8_data_to_file(f, json.dumps(self.config, indent=2))

    def get(self, name):
        if name not in self.config.keys():
            return self.default_config[name]["value"]
        return self.config[name]["value"]
