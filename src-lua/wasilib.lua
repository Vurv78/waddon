local __WASI_ESUCCESS = 0
local __WASI_EBADF = 8
local __WASI_FILETYPE_CHARACTER_DEVICE = 2

-- Taken from https://github.com/SwadicalRag/wasm2lua/blob/4dea912503b03238f8664cd2ec3503641294bf8b/resources/wasilib.lua

return function(memory)
	local WASI = {}

	function WASI.fd_fdstat_get(fd, out_buf)
		if fd <= 2 then
			memory:write8(out_buf + 0, __WASI_FILETYPE_CHARACTER_DEVICE)
			memory:write16(out_buf + 2, 0)
			memory:write32(out_buf + 8, 0)
			memory:write32(out_buf + 12, 0)
			memory:write32(out_buf + 16, 0)
			memory:write32(out_buf + 20, 0)

			return __WASI_ESUCCESS
		end

		return __WASI_EBADF
	end

	function WASI.fd_write(fd, iovec, iovec_len, out_count)
		local len_written = 0

		-- only stdio supported
		if fd == 1 or fd == 2 then
			local str = ""

			for i = 1, iovec_len do
				local ptr = memory:read32(iovec)
				local len = memory:read32(iovec + 4)

				for j = ptr, ptr + len - 1 do
					str = str .. string.char(memory:read8(j))
				end

				len_written = len_written + len
				iovec = iovec + 8
			end

			if fd == 1 then
				io.stdout:write(str)
			else
				io.stderr:write(str)
			end
		else
			return __WASI_EBADF
		end

		memory:write32(out_count, len_written)

		return __WASI_ESUCCESS
	end

	WASI.proc_exit = os.exit

	return WASI
end