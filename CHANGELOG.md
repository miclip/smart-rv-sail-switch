# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Blower simulator test rig for bench testing
- CI/CD pipeline for automated firmware builds
- GitHub Actions workflow for releases

## [v0.1.0] - Initial Development

### Added
- Smart Sail Switch firmware with pressure sensor
- Hybrid mode operation (parallel with original sail switch)
- MPXV5004DP differential pressure sensor support
- Wokwi simulation environment
- PlatformIO build system
- Documentation and schematics

### Features
- Airflow detection via differential pressure
- Automatic relay bypass on sail switch failure
- Safe-state operation (relay open by default)
- Visual status LEDs (idle/active)
- Configurable pressure thresholds
- Blower motor detection

[Unreleased]: https://github.com/miclip/smart-rv-sail-switch/compare/v0.1.0...HEAD
[v0.1.0]: https://github.com/miclip/smart-rv-sail-switch/releases/tag/v0.1.0
