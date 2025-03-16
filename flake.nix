{
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs = {
    self,
    nixpkgs,
  }: let
    pkgs = import nixpkgs {system = "x86_64-linux";};

    developEnv = pkgs.clangStdenv;
  in {
    devShells.x86_64-linux.default = pkgs.mkShell.override {stdenv = developEnv;} {
      name = "developEnv";
      packages = with pkgs; [
        pkg-config
        libGL
        SDL2
        SDL2_image
        cmake
      ];
    };
  };
}