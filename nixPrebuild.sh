#!/bin/bash

# This sets the version in TeamCity
export IN_VERSION=$(cat APP_VERSION)
echo "##teamcity[setParameter name='env.APP_VERSION' value='$IN_VERSION']"
