```shell
# install rust and cargo
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
# create project folder
cargo init mc
cd mc/
# compile and run
cp ../rust_files/mc.rs ./src/main.rs
cp ../rust_files/Cargo.toml ./Cargo.toml
cargo build --release
time ./target/release/mc 10000 4
```