#!/bin/bash
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 1024 -soundhw pcspk -serial stdio -no-kvm -snapshot
