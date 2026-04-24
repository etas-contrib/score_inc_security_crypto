# Steps to run demo without bazel (integration environment)

## Prepare Environment

```
bazel build //score/... //tests/...

mkdir -p /opt/crypto/tests/test_vectors/config
mkdir -p /opt/crypto/deploy
cp -r ./tests/test_vectors /opt/crypto/tests/
cp -r bazel-bin/tests/test_vectors /opt/crypto/tests/
cp -r tests/test_vectors/config/*.kv /opt/crypto/deploy

./bazel-bin/tests/integration_tests/init_softhsm_token \
  --token-dir /tmp/softhsm_tokens \
  --config-path /tmp/softhsm2.conf \
  --token-label SoftHSM \
  --so-pin 12345678 \
  --user-pin 1234 \
  --import-key-file /opt/crypto/tests/test_vectors/mac/key_aes_256.key \
  --import-key-label integration_test_hmac
```

## Start Daemon

```
export CRYPTO_CONFIG_FILE=/opt/crypto/tests/test_vectors/config/integration_test_config.bin
export SOFTHSM2_CONF=/tmp/softhsm2.conf

./bazel-bin/score/crypto/daemon/crypto_daemon
```

## Start Demo

```
./bazel-bin/tests/integration_tests/score_demo
```
