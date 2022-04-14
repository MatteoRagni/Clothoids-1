from setuptools import find_packages
from setuptools import setup

import sys

#############################
PACKAGE_NAME = "G2lib"
PACKAGE_VERSION = open("./VERSION").read().strip()
#############################

#  ___      _             
# / __| ___| |_ _  _ _ __ 
# \__ \/ -_)  _| || | "_ \
# |___/\___|\__|\_,_| .__/
#                   |_|   


setup(
    name=PACKAGE_NAME,
    version= PACKAGE_VERSION,
    packages=find_packages(exclude=["test"]),
    description="Geometric manipulation library for curves",
    zip_safe=False,
    package_data={
        "": ["*.so", "*.pyd"]
    },
    install_requires=[
        "setuptools"
    ],
    python_requires=">=3.6",
    
    author="Matteo Ragni",
    author_email="info@ragni.me",
    maintainer="Matteo Ragni",
    maintainer_email="info@ragni.me",
    license=open("./LICENSE").read(),
    keywords=["Clothoids", "Polyline", "Biarc", "Arc"],
    classifiers=[
        "Intended Audience :: Developers",
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python",
        "Topic :: Scientific/Engineering :: Mathematics",
        "Topic :: Software Development :: Libraries"
    ],
    project_urls={
        "Source": "https://github.com/MatteoRagni/Clothoids-1",
        "Tracker": "https://github.com/MatteoRagni/Clothoids-1"
    },
    url="https://github.com/MatteoRagni/Clothoids-1"
)