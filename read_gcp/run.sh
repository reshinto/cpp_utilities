#!/bin/sh
# chmod a+x run.sh

docker run -e GOOGLE_APPLICATION_CREDENTIALS=/app/credentials.json -v /Users/springfield/dev/google_credentials/shared/credentials.json:/app/credentials.json gcs-reader
