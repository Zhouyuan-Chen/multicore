```shell
# install rust and cargo
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
# create project folder
cargo init ps
cd ps/
# compile and run
cp ../rust_files/ps.rs ./src/main.rs
cp ../rust_files/Cargo.toml ./Cargo.toml
cargo build --release
time ./target/release/ps 4
```
