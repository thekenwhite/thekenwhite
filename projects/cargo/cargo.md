# cargo

```
- src/
	- bin/
		- _.rs
	- lib/
		- _.rs
- Cargo.toml
```

- `src/bin/_.rs`

```rust
fn main() {
	lib::run();
}
```

- `src/lib/_rs`

```rust
pub run() {
	println!("Hello, world!");
}
```

- `Cargo.toml`

```toml
[package]
name = "cargo"
version = "0.1.0"
edition = "2024"
default-run = "_"

[[bin]]
name = "_"
path = "src/bin/_.rs"

[lib]
name = "lib"
path = "src/lib/_.rs"
```
