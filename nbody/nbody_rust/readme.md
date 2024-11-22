```shell
# install rust and cargo
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
# create project folder
cargo init nbody
cd nbody/
# compile
cp ../rust_files/nbody.rs ./src/main.rs
cp ../rust_files/Cargo.toml ./Cargo.toml
cargo build --release
# run 
# example: 1000 particles, 1000 steps, 4 threads
cargo run --release 1000 1000 4
# timing
time ./target/release/nbody 1000 1000 4
```
