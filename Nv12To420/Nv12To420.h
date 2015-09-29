//
//  Nv12To420.h
//  Nv12To420
//
//  Created by Hank Lee on 5/31/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//
#ifndef ___NV12_TO_420___
#define ___NV12_TO_420___

int interleave_to_planar
(
        uint32_t wxh,
        uint8_t *u,
        uint8_t *v,
  const uint8_t *uv
);

#endif
