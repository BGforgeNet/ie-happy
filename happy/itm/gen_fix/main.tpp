READ_BYTE  0x18 "flags"
PATCH_IF (("%flags%" BAND 0b00000100) = 0b00000100) BEGIN  // droppable
  PATCH_INCLUDE ~%comp_dir%/set_2_hand.tpp~
  PATCH_INCLUDE ~%comp_dir%/null_missing_used_up.tpp~
  PATCH_INCLUDE ~%comp_dir%/create_missing_store_link.tpp~
  PATCH_INCLUDE ~%comp_dir%/fix_type.tpp~
  PATCH_INCLUDE ~%comp_dir%/assign_icons.tpp~
  PATCH_INCLUDE ~%comp_dir%/delete_invalid_abilities.tpp~
  PATCH_INCLUDE ~%comp_dir%/assign_ability_icons.tpp~
  PATCH_INCLUDE ~%comp_dir%/fix_ability_slot.tpp~
  PATCH_INCLUDE ~%comp_dir%/fix_ability_animation.tpp~
END
PATCH_INCLUDE ~%comp_dir%/fix_enchantment.tpp~
PATCH_INCLUDE ~%comp_dir%/fix_eq_effect.tpp~
PATCH_INCLUDE ~%comp_dir%/fix_eq_duration.tpp~
PATCH_INCLUDE ~%comp_dir%/fix_alt_damage.tpp~
PATCH_INCLUDE ~%comp_dir%/fix_strrefs.tpp~
PATCH_INCLUDE ~%comp_dir%/fix_ext_fx_duration.tpp~
PATCH_INCLUDE ~%comp_dir%/fix_prof.tpp~
PATCH_INCLUDE ~%comp_dir%/fix_paperdoll_anim.tpp~
PATCH_INCLUDE ~%comp_dir%/check_inventory_bam.tpp~
PATCH_INCLUDE ~%comp_dir%/fix_melee_projectile.tpp~
PATCH_INCLUDE ~%comp_dir%/fix_melee_charges.tpp~
PATCH_INCLUDE ~%comp_dir%/fix_melee_target.tpp~
