#!/bin/bash
# Script to reset data volume
INITIAL_DATA_PATH=/workspaces/cool-db/data/seed
DATA_VOLUME_PATH=/workspaces/cool-db/data/live

# Ensure initial data directory exists
mkdir -p $INITIAL_DATA_PATH

# Copy initial data to volume
cp -r $INITIAL_DATA_PATH/* $DATA_VOLUME_PATH/