```shell
# install rust and cargo
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
# create project folder
cargo init knn_rs
cd knn_rs/
# compile
cp ../rust_files/knn.rs ./src/main.rs
cp ../rust_files/Cargo.toml ./Cargo.toml
cargo build --release
# run 
# example: 10000 training points, 1000 testing points, 4 threads
cargo run --release 1000 1000 4
# timing
time ./target/release/nbody 1000 1000 4
```
