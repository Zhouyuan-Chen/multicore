```shell
# install rust and cargo
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# build
cargo build --release

# test, 
# M N K for two matrixs, t is the thread number
./target/release/mm_rust M N K t
```