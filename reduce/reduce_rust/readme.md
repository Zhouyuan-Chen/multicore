```shell
# install rust and cargo
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# build
cargo build --release

# test, N is the number of array, t is the thread number
./target/release/reduce_rust N t
```