local tbl = require("Utilities.TableUtil")
local mth = require("Utilities.MathUtil")
local util = {}

util.applyNoise = function(_path, _noiseSeed, _noiseDiv, _noiseScale, _sampleDist)
    if _path:itemType() == ItemType.Group then
        for _,child in ipairs(_path:children()) do
            util.applyNoise(upCastItem(child), _noiseSeed, _noiseDiv, _noiseScale, _sampleDist)
        end
    elseif _path:itemType() == ItemType.Path then
        if _path:length() <= _sampleDist then return end
        _path:flattenRegular(_sampleDist, false)
        for _,seg in ipairs(_path:segments()) do
            local pos = seg:position()
            local n1 = noise(pos.x / _noiseDiv, pos.y / _noiseDiv, _noiseSeed)
            pos = pos + Vec2(math.cos(n1 * math.pi * 2) * _noiseScale, math.sin(n1 * math.pi * 2) * _noiseScale)
            seg:setPosition(pos)
        end

        _path:smooth(Smoothing.Continuous, false)
    end
end

util.applyFBM = function(_path, _noiseSeed, _noiseDiv, _noiseScale, _sampleDist, _octaves)
    for i=1, _octaves, 1 do
        util.applyNoise(_path, _noiseSeed, _noiseDiv, _noiseScale, _sampleDist)
        _noiseDiv = _noiseDiv * 2.0
        _noiseScale = _noiseScale * 0.5
        _sampleDist = _sampleDist * 0.5
    end
end

util.matchSegmentCount = function(_a, _b)
    if _a:segmentCount() == _b:segmentCount() then return end
    local function match(_one, _two)
        while _one:segmentCount() < _two:segmentCount() do
            local longestCurve
            local curLen = 0
            for i,v in ipairs(_one:curves()) do
                if v:length() > curLen then
                    longestCurve = v
                    curLen = v:length()
                end
            end
            assert(longestCurve)
            longestCurve:divideAtParameter(0.5)
        end
    end
    if _a:segmentCount() < _b:segmentCount() then
        match(_a, _b)
    else
        match(_b, _a)
    end
end

util.morph = function(_path, _a, _b, _t)
    _path:removeSegments()
    -- print(_a:segmentCount(), _b:segmentCount())
    for i=1,_a:segmentCount(),1 do
        local aseg = _a:segment(i-1)
        local bseg = _b:segment(i-1)
        _path:addSegment(mth.mix(aseg:position(), bseg:position(), _t), mth.mix(aseg:handleIn(), bseg:handleIn(), _t), mth.mix(aseg:handleOut(), bseg:handleOut(), _t))
    end
    if _a:isClosed() then
        _path:closePath()
    end
end

util.arcify = function(_path, _sampleDist, _bClockwise)
    local ret = _path:document():createPath()
    local off = 0
    local len = _path:length()
    while off < len do
        local pos = _path:positionAt(math.min(len, off))
        if off == 0 then
            ret:addPoint(pos)
        else
            ret:arcTo(pos, _bClockwise)
        end
        off = off + _sampleDist
    end

    if off - len < _sampleDist then
        ret:arcTo(_path:positionAt(len), _bClockwise)
    end

    if _path:isClosed() then
        ret:closePath()
    end
    return ret
end

util.tubify = function(_path, _sampleDist, _radiusFn, _startFn, _endFn)
    local ret = _path:document():createPath()
    local len = _path:length()
    local off = 0
    local otherSidePos = {}
    local first, last, lastNormal, firstNormal

    local function addPoint(_off)
        local m = math.min(len, _off)
        local cl = _path:curveLocationAt(m)
        local n = cl:normal()
        local rad = _radiusFn(m, len, m / len)
        local p = cl:position() + n * rad
        ret:addPoint(p)
        table.insert(otherSidePos, cl:position() - n * rad)
        return cl, n, rad, p
    end

    while off < len do
        local cl, n, rad, p = addPoint(off)
        if off == 0 then
            first = p
            firstNormal = n
        end
        last = p
        lastNormal = n
        off = off + _sampleDist
    end

    if off - len < off then
        addPoint(len)
    end

    tbl.reverseInPlace(otherSidePos)
    _endFn(ret, last, otherSidePos[1], lastNormal)
    ret:arcTo(otherSidePos[1], true)

    table.remove(otherSidePos, 1)
    for _, v in ipairs(otherSidePos) do
        ret:addPoint(v)
        last = v
    end

    _startFn(ret, last, first, firstNormal * -1)

    return ret
end

return util
