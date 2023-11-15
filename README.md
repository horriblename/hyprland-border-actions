# Hyprland border actions

_`general:resize_on_border` must be set to true for this plugin to work_

This plugin extends the `general:resize_on_border` feature:

- Left Click on Borders to resize
- Right Click on Borders to move
- Middle Click to close window

## Installing
### with Hyprload

This is untested, let me know if you see a problem

```toml
plugins = [
  { git = "https://github.com/horriblename/hyprland-border-actions", branch = "main", name = "border-actions" },
]
```

### via nix

flakes are highly recommended (because I don't know how to do anything without it)

put this in your flake.nix

```nix
{
   inputs = {
      # ...
      hyprland.url = "github:hyprwm/Hyprland";
      hyprland-border-actions = {
         url = "github:horriblename/hyprland-border-actions";
         inputs.hyprland.follows = "hyprland"; # IMPORTANT
      };
   };
}
```
then, inside your home-manager module:

```nix
wayland.windowManager.hyprland = {
   plugins = [
      inputs.hyprland-border-actions.packages.${pkgs.system}.default
   ];
};
```
